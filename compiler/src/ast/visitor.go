package ast

import (
	"strconv"
	"token"
	"errors"
)

type Visitor interface {
	VisitVarDecl(node *VarDecl)
	VisitFunc(node *FuncDecl)

	VisitBadExpr(node *BadExpr)
	VisitBasicLit(node *BasicLit)
	VisitIdent(node *Ident)
	VisitUnaryExpr(node *UnaryExpr)
	VisitBinaryExpr(node *BinaryExpr)
	VisitArrayType(node *ArrayType)
	VisitCallExpr(node *CallExpr)

	VisitDeclStmt(node *DeclStmt)
	VisitEmptyStmt(node *EmptyStmt)
	VisitExprStmt(node *ExprStmt)
	VisitAssignStmt(node *AssignStmt)
	VisitReturnStmt(node *ReturnStmt)
	VisitBlockStmt(node *BlockStmt)
	VisitIfStmt(node *IfStmt)
	VisitForStmt(node *ForStmt)
	VisitFileAst(node *FileAst)
}

type ScopeCreatorVisitor struct {
	TopScope     *Scope
	currentScope *Scope
}

func (self *ScopeCreatorVisitor) VisitVarDecl(node *VarDecl) {
	node.Name.Obj = self.createVar(self.currentScope, node.Name.Name, node.Type)
}

func (self *ScopeCreatorVisitor) VisitFunc(node *FuncDecl) {
	node.Name.Obj = self.createFunc(self.currentScope, node.Name.Name, node.RetType, node.Params)	
	node.Name.Accept(self)
	
	self.createNewScope(self.currentScope)
	for i := 0; i < len(node.Params); i++ {	
		node.Params[i].Name.Obj = self.createVar(self.currentScope, node.Params[i].Name.Name, node.Params[i].Type)
		node.Params[i].Name.Accept(self)
	}
	
	node.Body.Accept(self)
	self.currentScope = self.currentScope.Outer
}

func (self *ScopeCreatorVisitor) VisitBadExpr(node *BadExpr) {
}
func (self *ScopeCreatorVisitor) VisitBasicLit(node *BasicLit) {
}
func (self *ScopeCreatorVisitor) VisitIdent(node *Ident) {
	node.Obj = self.currentScope.LookupDeep(node.Name)
}
func (self *ScopeCreatorVisitor) VisitUnaryExpr(node *UnaryExpr) {
	node.X.Accept(self)
}
func (self *ScopeCreatorVisitor) VisitBinaryExpr(node *BinaryExpr) {
	node.X.Accept(self)
	node.Y.Accept(self)
}
func (self *ScopeCreatorVisitor) VisitArrayType(node *ArrayType) {
	node.At.Accept(self)
}
func (self *ScopeCreatorVisitor) VisitCallExpr(node *CallExpr) {
	node.Fun.Accept(self)	
	
	for i := 0; i < len(node.Args); i++ {
		node.Args[i].Accept(self)
	}
}

func (self *ScopeCreatorVisitor) VisitDeclStmt(node *DeclStmt) {
	node.Decl.Accept(self)
}
func (self *ScopeCreatorVisitor) VisitEmptyStmt(node *EmptyStmt) {
}
func (self *ScopeCreatorVisitor) VisitExprStmt(node *ExprStmt) {
	node.X.Accept(self)
}
func (self *ScopeCreatorVisitor) VisitAssignStmt(node *AssignStmt) {
	node.Ident.Accept(self)
	node.X.Accept(self)	
}
func (self *ScopeCreatorVisitor) VisitReturnStmt(node *ReturnStmt) {
	node.X.Accept(self)
}
func (self *ScopeCreatorVisitor) VisitBlockStmt(node *BlockStmt) {
	self.createNewScope(self.currentScope)
	for i := 0; i < len(node.List); i++ {
		node.List[i].Accept(self)
	}
	self.currentScope = self.currentScope.Outer
}
func (self *ScopeCreatorVisitor) VisitIfStmt(node *IfStmt) {
	node.Cond.Accept(self)
	node.Body.Accept(self)
	if node.Else != nil {
		node.Else.Accept(self)
	}	
}
func (self *ScopeCreatorVisitor) VisitForStmt(node *ForStmt) {
	node.X.Accept(self)
	node.Body.Accept(self)
}

func (self *ScopeCreatorVisitor) VisitFileAst(node *FileAst) {
	self.createNewScope(nil)
	self.TopScope = self.currentScope
	for i := 0; i < len(node.Decls); i++ {
		node.Decls[i].Accept(self)
	}
	
	mainFunc := self.TopScope.Lookup("main")
	if mainFunc == nil || mainFunc.Kind != Fun {
		panic(errors.New("Not found main func"))
	}
}

func (self *ScopeCreatorVisitor) createNewScope(scope *Scope) {
	newScope := NewScope(scope)
	self.currentScope = newScope	
}

func (self *ScopeCreatorVisitor) createVar(scope *Scope, name string, objType Expression) (*Object) {
	createdObj := scope.Lookup(name)
	if createdObj != nil {
		panic(errors.New("Variable with name " + name + " already exist"))
	}
	variable := Object{
		Name: name,
		Kind: Var,
		Type: objType,
	}
	scope.Insert(&variable)
	return &variable
}

func (self *ScopeCreatorVisitor) createFunc(scope *Scope, name string, objType Expression, params []Field) (*Object) {
	createdObj := scope.Lookup(name)
	if createdObj != nil {
		panic(errors.New("Function with name " + name + " already exist"))
	}
	function := Object{
		Name: name,
		Kind: Fun,
		Decl: params,
		Type: objType,
	}
	scope.Insert(&function)
	return &function
}

// ------------------------------------------------------------------------------------

type AstCheckerVisitor struct {
}

func (self *AstCheckerVisitor) VisitVarDecl(node *VarDecl) {
}
func (self *AstCheckerVisitor) VisitFunc(node *FuncDecl) {
	for i := 0; i < len(node.Params); i++ {	
		node.Params[i].Name.Accept(self)
	}
	node.Body.Accept(self)
}
func (self *AstCheckerVisitor) VisitBadExpr(node *BadExpr) {
}
func (self *AstCheckerVisitor) VisitBasicLit(node *BasicLit) {
}
func (self *AstCheckerVisitor) VisitIdent(node *Ident) {	
}
func (self *AstCheckerVisitor) VisitUnaryExpr(node *UnaryExpr) {
	node.X.Accept(self)
}
func (self *AstCheckerVisitor) VisitBinaryExpr(node *BinaryExpr) {
	node.X.Accept(self)
	node.Y.Accept(self)
}
func (self *AstCheckerVisitor) VisitArrayType(node *ArrayType) {
	node.At.Accept(self)
}

func (self *AstCheckerVisitor) VisitCallExpr(node *CallExpr) {
	node.Fun.Accept(self)
	switch ident := node.Fun.(type) {
		case *Ident:
			decleredFunc := ident.Obj			
			if (len(node.Args) != len(decleredFunc.GetFuncDecl())) {
				panic(errors.New("Incorrect number of parameters in call func " + ident.Name))
			}
	}
	for i := 0; i < len(node.Args); i++ {
		node.Args[i].Accept(self)
	}
}
func (self *AstCheckerVisitor) VisitDeclStmt(node *DeclStmt) {
	node.Decl.Accept(self)
}
func (self *AstCheckerVisitor) VisitEmptyStmt(node *EmptyStmt) {
}
func (self *AstCheckerVisitor) VisitExprStmt(node *ExprStmt) {
	node.X.Accept(self)
}
func (self *AstCheckerVisitor) VisitAssignStmt(node *AssignStmt) {
	node.Ident.Accept(self)
	node.X.Accept(self)	
}
func (self *AstCheckerVisitor) VisitReturnStmt(node *ReturnStmt) {
	node.X.Accept(self)
}
func (self *AstCheckerVisitor) VisitBlockStmt(node *BlockStmt) {
	for i := 0; i < len(node.List); i++ {
		node.List[i].Accept(self)
	}
}
func (self *AstCheckerVisitor) VisitIfStmt(node *IfStmt) {
	node.Body.Accept(self)
	if node.Else != nil {
		node.Else.Accept(self)
	}
}
func (self *AstCheckerVisitor) VisitForStmt(node *ForStmt) {
	node.X.Accept(self)
	node.Body.Accept(self)
}
func (self *AstCheckerVisitor) VisitFileAst(node *FileAst) {
	typeChecker := new(TypeCheckerVisitor)
	for i := 0; i < len(node.Decls); i++ {
		node.Decls[i].Accept(self)
		node.Decls[i].Accept(typeChecker)
	}
}

// ------------------------------------------------------------------------------------

type TypeCheckerVisitor struct {
	Type CheckType
}

type CheckType int
const (
	INT CheckType = iota
	FLOAT
	STRING
	BOOLEAN
	ARRAY
)

func (self *TypeCheckerVisitor) VisitVarDecl(node *VarDecl) {
	self.Type = self.getExpressionType(node.Type)
}
func (self *TypeCheckerVisitor) VisitFunc(node *FuncDecl) {
	self.Type = self.getExpressionType(node.RetType)
	node.Body.Accept(self)
	switch stmt := node.Body.List[len(node.Body.List) - 1].(type) {
		case *ReturnStmt:
			stmt.X.Accept(self)
		default:
			panicFromToken("Function " + node.Name.Name + " has not return stmt", node.Name.T)
	}
}
func (self *TypeCheckerVisitor) VisitBadExpr(node *BadExpr) {
}
func (self *TypeCheckerVisitor) VisitBasicLit(node *BasicLit) {
	if (self.Type != self.getExpressionType(node)) {
		panicFromToken("Not equal expression types in BasicLit", node.T)
	}
}
func (self *TypeCheckerVisitor) VisitIdent(node *Ident) {
	if (self.Type != self.getExpressionType(node)) {
		panicFromToken("Not equal expression types in Identifier", node.T)
	}
}
func (self *TypeCheckerVisitor) VisitUnaryExpr(node *UnaryExpr) {
	if (self.Type != self.getExpressionType(node)) {
		panicFromToken("Not equal expression types in Identifier", node.OpT)
	}
	node.X.Accept(self)
}
func (self *TypeCheckerVisitor) VisitBinaryExpr(node *BinaryExpr) {
	isBooleanOperation := self.isBooleanToken(node.OpT)
	if self.Type == BOOLEAN && !isBooleanOperation {
		panicFromToken("Incorrect expr type, boolean operation expected", node.OpT)
	} else if self.Type != BOOLEAN && isBooleanOperation {
		panicFromToken("Incorrect expr type, unexpected boolean operation", node.OpT)
	}
	
	firstExpressionType  := self.getExpressionType(node.X)
	secondExpressionType := self.getExpressionType(node.Y)
	if firstExpressionType != secondExpressionType {
		panicFromToken("Not equal expression types", node.OpT)
	}
	if self.Type != BOOLEAN && self.Type != firstExpressionType {
		panicFromToken("Incorrect expression types", node.OpT)
	}
	var expectedType CheckType
	if node.OpT.TokenType == token.AND || node.OpT.TokenType == token.OR {
		expectedType = BOOLEAN
	} else {
		expectedType = firstExpressionType
	}
	self.Type = expectedType
	node.X.Accept(self)
	self.Type = expectedType
	node.Y.Accept(self)
}
func (self *TypeCheckerVisitor) VisitArrayType(node *ArrayType) {
	node.At.Accept(self)
}

func (self *TypeCheckerVisitor) VisitCallExpr(node *CallExpr) {	
	node.Fun.Accept(self)
	switch ident := node.Fun.(type) {
		case *Ident:
			decleredFunc := ident.Obj
			funDecls := decleredFunc.GetFuncDecl()
			for i := 0; i < len(node.Args); i++ {
				self.Type = self.getExpressionType(funDecls[i].Type)
				node.Args[i].Accept(self)
			}
		default:
			panic(errors.New("node.Fun is not indentifier"))
	}	
}
func (self *TypeCheckerVisitor) VisitDeclStmt(node *DeclStmt) {
	node.Decl.Accept(self)
}
func (self *TypeCheckerVisitor) VisitEmptyStmt(node *EmptyStmt) {
}
func (self *TypeCheckerVisitor) VisitExprStmt(node *ExprStmt) {
	if (self.Type != self.getExpressionType(node)) {
		panic(errors.New("Not equal expression types"))
	}
	node.X.Accept(self)
}
func (self *TypeCheckerVisitor) VisitAssignStmt(node *AssignStmt) {
	self.Type = self.getExpressionType(node.Ident)
	if (self.Type != self.getExpressionType(node.X)) {
			switch x := node.Ident.(type) {		
			case *Ident:
				panicFromToken("Not equal expression types in assign stmt", x.T)
			default:
				panic(errors.New("node.Ident is not indentifier"))
		}
	}
	node.X.Accept(self)	
}
func (self *TypeCheckerVisitor) VisitReturnStmt(node *ReturnStmt) {
	node.X.Accept(self)
}
func (self *TypeCheckerVisitor) VisitBlockStmt(node *BlockStmt) {
	for i := 0; i < len(node.List); i++ {
		node.List[i].Accept(self)
	}
}
func (self *TypeCheckerVisitor) VisitIfStmt(node *IfStmt) {
	self.Type = BOOLEAN
	node.Cond.Accept(self)
	node.Body.Accept(self)
	if node.Else != nil {
		node.Else.Accept(self)
	}
}
func (self *TypeCheckerVisitor) VisitForStmt(node *ForStmt) {
	self.Type = BOOLEAN
	node.X.Accept(self)
	node.Body.Accept(self)
}
func (self *TypeCheckerVisitor) VisitFileAst(node *FileAst) {
	for i := 0; i < len(node.Decls); i++ {
		node.Decls[i].Accept(self)
	}
}
	
func (self *TypeCheckerVisitor) getExpressionType(expr NodeAst) (CheckType) {
	switch x := expr.(type) {
		case *BadExpr:
			// do nothing
		case *BasicLit:
			if x.T.TokenType == token.INT_NUMBER || x.T.TokenType == token.INT {
				return INT
			} else if x.T.TokenType == token.FLOAT_NUMBER || x.T.TokenType == token.FLOAT {
				return FLOAT
			} else if x.T.TokenType == token.STRING_VALUE || x.T.TokenType == token.STRING {
				return STRING
			} else {
				panicFromToken("undefined expression type from BasicLit", x.T)
			}
		case *Ident:
			return self.getExpressionType(x.Obj.GetType())
		case *UnaryExpr:
			return self.getExpressionType(x.X)
		case *BinaryExpr:								
			if self.isBooleanToken(x.OpT) {
				return BOOLEAN
			} else {
				return self.getExpressionType(x.X)
			}
		case *ArrayType:
			return self.getExpressionType(x.At)
		case *CallExpr:
			return self.getExpressionType(x.Fun)
		default:
			panic(errors.New("undefined expression type"))
	}

	return BOOLEAN
}

func (self *TypeCheckerVisitor) isBooleanToken(t token.Token) bool {
	return t.TokenType == token.EQUAL || t.TokenType == token.NOT_EQUAL ||
		   t.TokenType == token.GREATE || t.TokenType == token.AND ||
		   t.TokenType == token.OR
}

func panicFromToken(msg string, t token.Token) {
	panic(errors.New(msg + " " + getErrorMessageFromToken(t)))
}

func getErrorMessageFromToken(t token.Token) string {
	return "token: " + t.Value + " at line: " + strconv.Itoa(t.RowIndex) +
	       ", column: " + strconv.Itoa(t.ColumnIndex)
}