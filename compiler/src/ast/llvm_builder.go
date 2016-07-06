package ast

/*
include "lib.c"
include <stdio.h>
*/
import (
	"C"
	"errors"
	"flag"
	"fmt"
	"os"
	"strconv"
	"token"

	"github.com/go-llvm/llvm"
)

var (
	rootModule      = llvm.NewModule("root")
	rootFuncPassMgr = llvm.NewFunctionPassManagerForModule(rootModule)
	builder         = llvm.NewBuilder()
	namedVals       = map[string]llvm.Value{}
	options         = llvm.NewMCJITCompilerOptions()
	execEngine      llvm.ExecutionEngine
	machine         llvm.TargetMachine

	printFun llvm.Value

	batch       = flag.Bool("b", false, "batch (non-interactive) mode")
	optimized   = flag.Bool("opt", true, "add some optimization passes")
	printTokens = flag.Bool("tok", false, "print tokens")
	printAst    = flag.Bool("ast", false, "print abstract syntax tree")
	printLLVMIR = flag.Bool("llvm", false, "print LLVM generated code")
	outputObj   = flag.String("obj", "", "output obj")
	verbose     = flag.Bool("verbose", false, "verbose output")
)

type LlvmBuilderVisitor struct {
	OutputFile string

	value  llvm.Value
	module llvm.Module
}

func (self *LlvmBuilderVisitor) VisitVarDecl(node *VarDecl) {
	generateVar(node)
}
func (self *LlvmBuilderVisitor) VisitFunc(node *FuncDecl) {

	funcArgs := []llvm.Type{}
	for i := 0; i < len(node.Params); i++ {
		paramType := getLlvmTypeByParamType(node.Params[i].Type)
		funcArgs = append(funcArgs, paramType)
	}

	funcType := createFuncType(node)
	functionType := llvm.FunctionType(funcType, funcArgs, false)
	function := llvm.AddFunction(self.module, node.Name.Name, functionType)

	if function.Name() != node.Name.Name {
		function.EraseFromParentAsFunction()
		function = self.module.NamedFunction(node.Name.Name)
	}
	if function.BasicBlocksCount() != 0 {
		panicFromToken("redefinition of function", node.Name.T)
	}
	if function.ParamsCount() != len(node.Params) {
		panicFromToken("redefinition of function with different numbers of args", node.Name.T)
	}
	node.Name.Obj.Data = function

	for i, param := range function.Params() {
		param.SetName(node.Params[i].Name.Name)
	}

	block := llvm.AddBasicBlock(function, node.Name.Name)
	builder.SetInsertPointAtEnd(block)

	for i, param := range function.Params() {
		generateParam(node.Params[i].Name, node.Params[i].Type)
		acceptParam(param, node.Params[i])
	}

	node.Body.Accept(self)

	builder.CreateRet(self.value)

	if llvm.VerifyFunction(function, llvm.PrintMessageAction) != nil {
		panicFromToken("Function verification failed", node.Name.T)
	}
}
func (self *LlvmBuilderVisitor) VisitBadExpr(node *BadExpr) {
}
func (self *LlvmBuilderVisitor) VisitBasicLit(node *BasicLit) {
	if node.T.TokenType == token.INT_NUMBER || node.T.TokenType == token.FLOAT_NUMBER {
		self.value = getNumber(node)
	} else if node.T.TokenType == token.STRING_VALUE || node.T.TokenType == token.STRING {
		panicFromToken("This version not support string values", node.T)
	}
}
func (self *LlvmBuilderVisitor) VisitIdent(node *Ident) {
	self.value = getVar(node)
}
func (self *LlvmBuilderVisitor) VisitUnaryExpr(node *UnaryExpr) {
	node.X.Accept(self)
	firstValue := self.value

	varType := getExpressionType(node.X)

	if varType == INT {
		panicFromToken("Not support unary operation", node.OpT)
	} else if varType == FLOAT {
		switch node.OpT.TokenType {
		case token.SUB:
			secondValue := llvm.ConstFloat(llvm.DoubleType(), -1)
			self.value = builder.CreateFMul(firstValue, secondValue, "subtmp")
		default:
			panicFromToken("Not support unary operation", node.OpT)
		}
	} else {
		panicFromToken("Not support unary operation type", node.OpT)
	}
}
func (self *LlvmBuilderVisitor) VisitBinaryExpr(node *BinaryExpr) {
	node.X.Accept(self)
	firstValue := self.value

	node.Y.Accept(self)
	secondValue := self.value

	varType := getExpressionType(node.X)

	if node.OpT.TokenType == token.LBRACK {
		switch x := node.X.(type) {
		case *Ident:
			alloca := x.Obj.GetAlloca()
			al := builder.CreateInBoundsGEP(alloca, []llvm.Value{secondValue}, "tmparr")
			self.value = builder.CreateLoad(al, x.Name)
		default:
			panicFromToken("Expr X is not array", node.OpT)
		}
	} else if varType == INT {
		switch node.OpT.TokenType {
		case token.ADD:
			self.value = builder.CreateAdd(firstValue, secondValue, "addtmp")
		case token.SUB:
			self.value = builder.CreateSub(firstValue, secondValue, "subtmp")
		case token.MUL:
			self.value = builder.CreateMul(firstValue, secondValue, "multmp")
		case token.QUO:
			self.value = builder.CreateUDiv(firstValue, secondValue, "divtmp")
		case token.EQUAL:
			self.value = builder.CreateICmp(llvm.IntEQ, firstValue, secondValue, "cmptmp")
		case token.NOT_EQUAL:
			self.value = builder.CreateICmp(llvm.IntNE, firstValue, secondValue, "cmptmp")
		case token.GREATE:
			self.value = builder.CreateICmp(llvm.IntSGT, firstValue, secondValue, "cmptmp")
		case token.LESS:
			self.value = builder.CreateICmp(llvm.IntSLT, firstValue, secondValue, "cmptmp")
		default:
			panicFromToken("Not support operation", node.OpT)
		}
	} else if varType == FLOAT {
		switch node.OpT.TokenType {
		case token.ADD:
			self.value = builder.CreateFAdd(firstValue, secondValue, "addtmp")
		case token.SUB:
			self.value = builder.CreateFSub(firstValue, secondValue, "subtmp")
		case token.MUL:
			self.value = builder.CreateFMul(firstValue, secondValue, "multmp")
		case token.QUO:
			self.value = builder.CreateFDiv(firstValue, secondValue, "divtmp")
		case token.EQUAL:
			self.value = builder.CreateFCmp(llvm.FloatOEQ, firstValue, secondValue, "cmptmp")
		case token.NOT_EQUAL:
			self.value = builder.CreateFCmp(llvm.FloatUNE, firstValue, secondValue, "cmptmp")
		case token.GREATE:
			self.value = builder.CreateFCmp(llvm.FloatOGT, firstValue, secondValue, "cmptmp")
		case token.LESS:
			self.value = builder.CreateFCmp(llvm.FloatOLT, firstValue, secondValue, "cmptmp")
		default:
			panicFromToken("Not support operation", node.OpT)
		}
	} else if varType == BOOLEAN {
		switch node.OpT.TokenType {
		case token.OR:
			self.value = builder.CreateOr(firstValue, secondValue, "ortmp")
		case token.AND:
			self.value = builder.CreateAnd(firstValue, secondValue, "andtmp")
		default:
			panicFromToken("Not support operation", node.OpT)
		}
	} else {
		panicFromToken("Not support operation type", node.OpT)
	}
}
func (self *LlvmBuilderVisitor) VisitArrayType(node *ArrayType) {
	builder := llvm.NewBuilder()
	builder.ClearInsertionPoint()
	node.At.Accept(self)
}

func (self *LlvmBuilderVisitor) VisitCallExpr(node *CallExpr) {
	switch x := node.Fun.(type) {
	case *Ident:

		args := make([]llvm.Value, len(node.Args))
		for i := range args {
			node.Args[i].Accept(self)
			args[i] = self.value
		}

		self.value = builder.CreateCall(x.Obj.GetAlloca(), args, "calltmp")
	default:
		panic(errors.New("node.fun is not indentifier in CallEpr"))
	}
}
func (self *LlvmBuilderVisitor) VisitDeclStmt(node *DeclStmt) {
	node.Decl.Accept(self)
}
func (self *LlvmBuilderVisitor) VisitEmptyStmt(node *EmptyStmt) {
}
func (self *LlvmBuilderVisitor) VisitExprStmt(node *ExprStmt) {
	node.X.Accept(self)
}
func (self *LlvmBuilderVisitor) VisitAssignStmt(node *AssignStmt) {
	node.X.Accept(self)
	val := self.value
	if self.value.IsNil() {
		panic(errors.New("Not calculated value"))
	}
	switch x := node.Ident.(type) {
	case *Ident:
		identType := getExpressionType(x)
		if isArrayType(identType) { // assign with arrays
			switch y := node.X.(type) {
			case *Ident:
				copyArray(y, x, x.Obj.GetArraySize())
			case *CallExpr:
				switch f := y.Fun.(type) {
				case *Ident:
					copyArray(f, x, x.Obj.GetArraySize())
				}
			default:
				panic(errors.New("node.X is not indentifier in assign expr with arrays"))
			}
		} else {
			alloca := x.Obj.GetAlloca()
			builder.CreateStore(val, alloca)
		}
	case *BinaryExpr:
		switch xx := x.X.(type) {
		case *Ident:
			x.Y.Accept(self)
			index := self.value
			alloca := xx.Obj.GetAlloca()
			al := builder.CreateInBoundsGEP(alloca, []llvm.Value{index}, "tmparr")
			builder.CreateStore(val, al)
		default:
			panicFromToken("node.Ident is not indentifier in BinaryEpr", x.OpT)
		}
	default:
		panic(errors.New("node.Ident is not indentifier"))
	}
}
func (self *LlvmBuilderVisitor) VisitPrintStmt(node *PrintStmt) {
	node.X.Accept(self)
	exprType := getExpressionType(node.X)
	if exprType == INT {
		args := make([]llvm.Value, 2)
		args[0] = builder.CreateGlobalStringPtr("%d\n", "format")
		args[1] = self.value
		builder.CreateCall(printFun, args, "printf")
	} else if exprType == FLOAT {
		args := make([]llvm.Value, 2)
		args[0] = builder.CreateGlobalStringPtr("%f\n", "format")
		args[1] = self.value
		builder.CreateCall(printFun, args, "printf")
	} else {
		panic(errors.New("Print support only int and float expression type"))
	}
}
func (self *LlvmBuilderVisitor) VisitReturnStmt(node *ReturnStmt) {
	node.X.Accept(self)
}
func (self *LlvmBuilderVisitor) VisitBlockStmt(node *BlockStmt) {
	for i := 0; i < len(node.List); i++ {
		node.List[i].Accept(self)
	}
}
func (self *LlvmBuilderVisitor) VisitIfStmt(node *IfStmt) {
	node.Cond.Accept(self)
	ifv := self.value
	condType := getExpressionType(node.Cond)

	parentFunc := builder.GetInsertBlock().Parent()
	thenBlk := llvm.AddBasicBlock(parentFunc, "then")
	elseBlk := llvm.AddBasicBlock(parentFunc, "else")
	mergeBlk := llvm.AddBasicBlock(parentFunc, "merge")
	builder.CreateCondBr(ifv, thenBlk, elseBlk)

	builder.SetInsertPointAtEnd(thenBlk)
	node.Body.Accept(self)

	thenvalInt := llvm.ConstInt(llvm.Int32Type(), 1, true)
	elsevalInt := llvm.ConstInt(llvm.Int32Type(), 0, true)

	thenvalFloat := llvm.ConstFloat(llvm.DoubleType(), 1)
	elsevalFloat := llvm.ConstFloat(llvm.DoubleType(), 0)

	builder.CreateBr(mergeBlk)
	thenBlk = builder.GetInsertBlock()
	builder.SetInsertPointAtEnd(elseBlk)

	if node.Else != nil {
		node.Else.Accept(self)
	}
	builder.CreateBr(mergeBlk)
	elseBlk = builder.GetInsertBlock()

	builder.SetInsertPointAtEnd(mergeBlk)

	if condType == INT {
		PhiNode := builder.CreatePHI(llvm.Int32Type(), "iftmp")
		PhiNode.AddIncoming([]llvm.Value{thenvalInt}, []llvm.BasicBlock{thenBlk})
		PhiNode.AddIncoming([]llvm.Value{elsevalInt}, []llvm.BasicBlock{elseBlk})
		self.value = PhiNode
	} else {
		PhiNode := builder.CreatePHI(llvm.DoubleType(), "iftmp")
		PhiNode.AddIncoming([]llvm.Value{thenvalFloat}, []llvm.BasicBlock{thenBlk})
		PhiNode.AddIncoming([]llvm.Value{elsevalFloat}, []llvm.BasicBlock{elseBlk})
		self.value = PhiNode
	}
}
func (self *LlvmBuilderVisitor) VisitForStmt(node *ForStmt) {
	node.X.Accept(self)
	forv := self.value

	parentFunc := builder.GetInsertBlock().Parent()
	loopBlk := llvm.AddBasicBlock(parentFunc, "loop")
	afterBlk := llvm.AddBasicBlock(parentFunc, "afterloop")
	builder.CreateCondBr(forv, loopBlk, afterBlk)

	builder.SetInsertPointAtEnd(loopBlk)

	node.Body.Accept(self)

	node.X.Accept(self)
	forv = self.value

	builder.CreateCondBr(forv, loopBlk, afterBlk)
	builder.SetInsertPointAtEnd(afterBlk)
}
func (self *LlvmBuilderVisitor) VisitFileAst(node *FileAst) {
	self.module = llvm.NewModule("compiler")

	// create our exe engine
	engine, err := llvm.NewExecutionEngine(self.module)
	if err != nil {
		fmt.Println(err.Error())
	}

	printFun = registerPrintFunc(self.module)

	for i := 0; i < len(node.Decls); i++ {
		node.Decls[i].Accept(self)
	}

	self.module.Dump()

	// verify it's all good
	if ok := llvm.VerifyModule(self.module, llvm.ReturnStatusAction); ok != nil {
		panic(errors.New(ok.Error()))
	}

	file, err := os.Create(self.OutputFile)
	if err != nil {
		panic(err)
	}
	llvm.WriteBitcodeToFile(self.module, file)

	// run the function!
	funcResult := engine.RunFunction(self.module.NamedFunction("main"), []llvm.GenericValue{})
	fmt.Printf("%d\n", funcResult.Int(false))
}

func getNumber(node *BasicLit) llvm.Value {
	if node.T.TokenType == token.INT_NUMBER {
		value, err := strconv.ParseUint(node.T.Value, 10, 64)
		if err != nil {
			panicFromToken("Can not convert to int32", node.T)
		}
		return llvm.ConstInt(llvm.Int32Type(), value, true)
	} else if node.T.TokenType == token.FLOAT_NUMBER {
		str := node.T.Value
		value, err := strconv.ParseFloat(str[0:len(str)-1], 64)
		if err != nil {
			panicFromToken("Can not convert to float", node.T)
		}
		return llvm.ConstFloat(llvm.DoubleType(), value)
	} else {
		panicFromToken("undefined expression type from BasicLit", node.T)
	}

	return llvm.ConstInt(llvm.Int32Type(), 0, false)
}

func copyArray(srcIdent *Ident, dscIdent *Ident, size uint64) {
	srcAlloca := srcIdent.Obj.GetAlloca()
	dscAlloca := dscIdent.Obj.GetAlloca()
	var i uint64
	for i = 0; i < size; i++ {
		srcAl := builder.CreateInBoundsGEP(srcAlloca, []llvm.Value{llvm.ConstInt(llvm.Int32Type(), i, false)}, "srctmparralloca")
		dscAl := builder.CreateInBoundsGEP(dscAlloca, []llvm.Value{llvm.ConstInt(llvm.Int32Type(), i, false)}, "dsctmparralloca")
		val := builder.CreateLoad(srcAl, "tmparrload")
		builder.CreateStore(val, dscAl)
	}
}

func getVar(node *Ident) llvm.Value {
	v := node.Obj.GetAlloca()
	if v.IsNil() {
		panicFromToken("Unknown variable name", node.T)
	}
	return builder.CreateLoad(v, node.Name)
}

func getLlvmTypeByParamType(expr NodeAst) llvm.Type {
	paramType := getExpressionType(expr)
	if paramType == INT {
		return llvm.Int32Type()
	} else if paramType == FLOAT {
		return llvm.DoubleType()
	} else {
		panic(errors.New("Arrays not support in functions in this version"))
	}
	return llvm.Int32Type()
}

func generateVar(node *VarDecl) {
	generateVariable(node.Name, node.Type)
}

func generateParam(node *Ident, x Expression) {
	generateVariable(node, x)
}

func acceptParam(param llvm.Value, field Field) {
	varType := getExpressionType(field.Type)
	if isArrayType(varType) {
		panicFromToken("Parameter of function can not be array in this version", field.Name.T)
	} else {
		builder.CreateStore(param, field.Name.Obj.GetAlloca())
	}
}

func generateVariable(ident *Ident, varTy Expression) {
	varType := getExpressionType(varTy)
	if varType == ARRAY_INT {
		alloca := builder.CreateArrayAlloca(llvm.Int32Type(), llvm.ConstInt(llvm.Int32Type(), ident.Obj.GetArraySize(), false), ident.Name)
		var i uint64
		for i = 0; i < ident.Obj.GetArraySize(); i++ {
			al := builder.CreateInBoundsGEP(alloca, []llvm.Value{llvm.ConstInt(llvm.Int32Type(), i, false)}, "tmparr")
			val := llvm.ConstInt(llvm.Int32Type(), 0, true)
			builder.CreateStore(val, al)
		}
		ident.Obj.Data = alloca
	} else if varType == ARRAY_FLOAT {
		alloca := builder.CreateArrayAlloca(llvm.DoubleType(), llvm.ConstInt(llvm.Int32Type(), ident.Obj.GetArraySize(), false), ident.Name)
		var i uint64
		for i = 0; i < ident.Obj.GetArraySize(); i++ {
			al := builder.CreateInBoundsGEP(alloca, []llvm.Value{llvm.ConstInt(llvm.Int32Type(), i, false)}, "tmparr")
			val := llvm.ConstFloat(llvm.DoubleType(), 0)
			builder.CreateStore(val, al)
		}
		ident.Obj.Data = alloca
	} else if varType == INT {
		alloca := builder.CreateAlloca(llvm.Int32Type(), ident.Name)
		val := llvm.ConstInt(llvm.Int32Type(), 0, true)
		builder.CreateStore(val, alloca)
		ident.Obj.Data = alloca
	} else if varType == FLOAT {
		alloca := builder.CreateAlloca(llvm.DoubleType(), ident.Name)
		val := llvm.ConstFloat(llvm.DoubleType(), 0)
		builder.CreateStore(val, alloca)
		ident.Obj.Data = alloca
	} else {
		panicFromToken("Not support variable type", ident.T)
	}
}

func createFuncType(node *FuncDecl) llvm.Type {
	result := llvm.Int32Type()
	switch stmt := node.Body.List[len(node.Body.List)-1].(type) {
	case *ReturnStmt:
		return getLlvmTypeByParamType(stmt.X)
	}
	return result
}

func registerPrintFunc(module llvm.Module) llvm.Value {

	funcArgs := []llvm.Type{}
	funcArgs = append(funcArgs, llvm.Int32Type())

	funcType := llvm.Int32Type()
	functionType := llvm.FunctionType(funcType, funcArgs, false)
	function := llvm.AddFunction(module, "printI", functionType)
	/*
		funcArgs := []llvm.Type{}
		funcArgs = append(funcArgs, llvm.PointerType(llvm.Int8Type(), 0))

		funcType := llvm.Int32Type()
		functionType := llvm.FunctionType(funcType, funcArgs, true)
		function := llvm.AddFunction(module, "printf", functionType)
	*/
	return function
}
