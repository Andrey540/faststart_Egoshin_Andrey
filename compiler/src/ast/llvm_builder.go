package ast

type LlvmBuilderVisitor struct {
}

func (self *LlvmBuilderVisitor) VisitVarDecl(node *VarDecl) {
}
func (self *LlvmBuilderVisitor) VisitFunc(node *FuncDecl) {
	for i := 0; i < len(node.Params); i++ {	
		node.Params[i].Name.Accept(self)
	}
	node.Body.Accept(self)
}
func (self *LlvmBuilderVisitor) VisitBadExpr(node *BadExpr) {
}
func (self *LlvmBuilderVisitor) VisitBasicLit(node *BasicLit) {
}
func (self *LlvmBuilderVisitor) VisitIdent(node *Ident) {	
}
func (self *LlvmBuilderVisitor) VisitUnaryExpr(node *UnaryExpr) {
	node.X.Accept(self)
}
func (self *LlvmBuilderVisitor) VisitBinaryExpr(node *BinaryExpr) {
	node.X.Accept(self)
	node.Y.Accept(self)
}
func (self *LlvmBuilderVisitor) VisitArrayType(node *ArrayType) {
	node.At.Accept(self)
}

func (self *LlvmBuilderVisitor) VisitCallExpr(node *CallExpr) {
	node.Fun.Accept(self)
	for i := 0; i < len(node.Args); i++ {
		node.Args[i].Accept(self)
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
	node.Ident.Accept(self)
	node.X.Accept(self)	
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
	node.Body.Accept(self)
	if node.Else != nil {
		node.Else.Accept(self)
	}
}
func (self *LlvmBuilderVisitor) VisitForStmt(node *ForStmt) {
	node.X.Accept(self)
	node.Body.Accept(self)
}
func (self *LlvmBuilderVisitor) VisitFileAst(node *FileAst) {
	for i := 0; i < len(node.Decls); i++ {
		node.Decls[i].Accept(self)
	}
}

type LlvmBuilder struct {
}