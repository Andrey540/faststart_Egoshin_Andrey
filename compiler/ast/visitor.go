package ast

import (
	"fmt"
	"strconv"
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

type PrintVisitor struct {
	msg string
}

func (self *PrintVisitor) VisitVarDecl(node *VarDecl) {
	fmt.Println("Variable Node. Name : " + node.Name.Name)
}

func (self *PrintVisitor) VisitFunc(node *FuncDecl) {
	fmt.Printf("Visit Func Decl. Name : ")
	node.Name.Accept(self)
	for i := 0; i < len(node.Params); i++ {
		fmt.Printf("With param : ")
		node.Params[i].Name.Accept(self)
	}
	fmt.Println()
	node.Body.Accept(self)
}

func (self *PrintVisitor) VisitBadExpr(node *BadExpr) {
	fmt.Printf("Visit Bad Expression")
}
func (self *PrintVisitor) VisitBasicLit(node *BasicLit) {
	fmt.Printf(string(node.T.Value))
}
func (self *PrintVisitor) VisitIdent(node *Ident) {
	fmt.Printf("Identifier: " + node.Name + " ")
}
func (self *PrintVisitor) VisitUnaryExpr(node *UnaryExpr) {
	fmt.Printf("Unary Expr: " + string(node.Op))
	node.X.Accept(self)
}
func (self *PrintVisitor) VisitBinaryExpr(node *BinaryExpr) {
	fmt.Printf(" Visit Binary Expr ")
	node.X.Accept(self)
	fmt.Printf(node.OpT.Value)
	node.Y.Accept(self)
}
func (self *PrintVisitor) VisitArrayType(node *ArrayType) {
	fmt.Printf("Visit Array Type with index : " + strconv.Itoa(node.Index))
	node.At.Accept(self)
}
func (self *PrintVisitor) VisitCallExpr(node *CallExpr) {
	fmt.Printf("Visit Call Expr : ")
	node.Fun.Accept(self)
	for i := 0; i < len(node.Args); i++ {
		node.Args[i].Accept(self)
		fmt.Printf(", ")
	}
}

func (self *PrintVisitor) VisitDeclStmt(node *DeclStmt) {
	fmt.Printf("Visit Decl Stmt ")
	node.Decl.Accept(self)
}
func (self *PrintVisitor) VisitEmptyStmt(node *EmptyStmt) {
	fmt.Println("Visit Empty Stmt")
}
func (self *PrintVisitor) VisitExprStmt(node *ExprStmt) {
	fmt.Printf("Visit Expr Stmt ")
	node.X.Accept(self)
}
func (self *PrintVisitor) VisitAssignStmt(node *AssignStmt) {
	fmt.Printf("Visit Assign Stmt ")
	node.Ident.Accept(self)
	fmt.Printf("= ")
	node.X.Accept(self)	
}
func (self *PrintVisitor) VisitReturnStmt(node *ReturnStmt) {
	fmt.Printf("Visit Return Stmt ")
	node.X.Accept(self)
}
func (self *PrintVisitor) VisitBlockStmt(node *BlockStmt) {
	fmt.Println("Visit Block Stmt")
	for i := 0; i < len(node.List); i++ {
		node.List[i].Accept(self)
		fmt.Println()
	}
}
func (self *PrintVisitor) VisitIfStmt(node *IfStmt) {
	fmt.Printf("Visit If Stmt")
	node.Cond.Accept(self)
	fmt.Println()
	node.Body.Accept(self)
	if node.Else != nil {
		node.Else.Accept(self)
	}	
}
func (self *PrintVisitor) VisitForStmt(node *ForStmt) {
	fmt.Printf("Visit For Stmt")
	node.X.Accept(self)
	node.Body.Accept(self)
}

func (self *PrintVisitor) VisitFileAst(node *FileAst) {
	fmt.Println("Visit File: ")
	for i := 0; i < len(node.Decls); i++ {
		node.Decls[i].Accept(self)
	}
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
	node.Obj = self.currentScope.LookupAll(node.Name)
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
	switch ident := node.Fun.(type) {
		case *Ident:
			decleredFunc := self.currentScope.LookupAll(ident.Name)
			
			if (len(node.Args) != len(decleredFunc.GetFuncDecl())) {
				panic(fmt.Sprintf("Incorrect number of parameters in call func " + ident.Name))
			}
		default:
			panic(fmt.Sprintf("node.Fun is not indentifier"))
	}
	
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
	switch node.Ident.(type) {
		case *Ident:
			// do nothing
		default:
			panic(fmt.Sprintf("node.Ident is not indentifier"))
	}
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
}

func (self *ScopeCreatorVisitor) createNewScope(scope *Scope) {
	newScope := NewScope(scope)
	self.currentScope = newScope
}

func (self *ScopeCreatorVisitor) createVar(scope *Scope, name string, objType Expression) (*Object) {
	createdObj := scope.Lookup(name)
	if createdObj != nil {
		panic(fmt.Sprintf("Variable with name " + name + " already exist"))
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
		panic(fmt.Sprintf("Function with name " + name + " already exist"))
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


type TypeCheckerVisitor struct {
	Type TypeCheckType
}

type TypeCheckType int
const (
	INT TypeCheckType = iota
	FLOAT
	STRING
	ARRAY
)

func (self *TypeCheckerVisitor) VisitVarDecl(node *VarDecl) {
}
func (self *TypeCheckerVisitor) VisitFunc(node *FuncDecl) {
}
func (self *TypeCheckerVisitor) VisitBadExpr(node *BadExpr) {
}
func (self *TypeCheckerVisitor) VisitBasicLit(node *BasicLit) {
	fmt.Printf(string(node.T.Value))
}
func (self *TypeCheckerVisitor) VisitIdent(node *Ident) {
	fmt.Printf("Identifier: " + node.Name + " ")
}
func (self *TypeCheckerVisitor) VisitUnaryExpr(node *UnaryExpr) {
	fmt.Printf("Unary Expr: " + string(node.Op))
	node.X.Accept(self)
}
func (self *TypeCheckerVisitor) VisitBinaryExpr(node *BinaryExpr) {
	fmt.Printf(" Visit Binary Expr ")
	node.X.Accept(self)
	fmt.Printf(node.OpT.Value)
	node.Y.Accept(self)
}
func (self *TypeCheckerVisitor) VisitArrayType(node *ArrayType) {
	fmt.Printf("Visit Array Type with index : " + strconv.Itoa(node.Index))
	node.At.Accept(self)
}

func (self *TypeCheckerVisitor) VisitCallExpr(node *CallExpr) {
	for i := 0; i < len(node.Args); i++ {
		node.Args[i].Accept(self)
	}
}
func (self *TypeCheckerVisitor) VisitDeclStmt(node *DeclStmt) {
	node.Decl.Accept(self)
}
func (self *TypeCheckerVisitor) VisitEmptyStmt(node *EmptyStmt) {
}
func (self *TypeCheckerVisitor) VisitExprStmt(node *ExprStmt) {
	node.X.Accept(self)
}
func (self *TypeCheckerVisitor) VisitAssignStmt(node *AssignStmt) {
	node.Ident.Accept(self)
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
	node.Cond.Accept(self)
	node.Body.Accept(self)
	if node.Else != nil {
		node.Else.Accept(self)
	}
}
func (self *TypeCheckerVisitor) VisitForStmt(node *ForStmt) {
	node.X.Accept(self)
	node.Body.Accept(self)
}
func (self *TypeCheckerVisitor) VisitFileAst(node *FileAst) {
	for i := 0; i < len(node.Decls); i++ {
		node.Decls[i].Accept(self)
	}
}