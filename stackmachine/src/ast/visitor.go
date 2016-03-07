package ast

import (
	"fmt"
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
	fmt.Println("Visit Func Decl")
}

func (self *PrintVisitor) VisitBadExpr(node *BadExpr) {
	fmt.Println("Visit Bad Expression")
}
func (self *PrintVisitor) VisitBasicLit(node *BasicLit) {
	fmt.Println(string(node.T.TokenType))
}
func (self *PrintVisitor) VisitIdent(node *Ident) {
	fmt.Println("Identifier: " + node.Name)
}
func (self *PrintVisitor) VisitUnaryExpr(node *UnaryExpr) {
	fmt.Println("Unary Expr: " + string(node.Op))
}
func (self *PrintVisitor) VisitBinaryExpr(node *BinaryExpr) {
	fmt.Println("Visit Func Decl")
}
func (self *PrintVisitor) VisitArrayType(node *ArrayType) {
	fmt.Println("Visit Func Decl")
}

func (self *PrintVisitor) VisitDeclStmt(node *DeclStmt) {
	fmt.Println("Visit Func Decl")
}
func (self *PrintVisitor) VisitEmptyStmt(node *EmptyStmt) {
	fmt.Println("Visit Func Decl")
}
func (self *PrintVisitor) VisitExprStmt(node *ExprStmt) {
	fmt.Println("Visit Func Decl")
}
func (self *PrintVisitor) VisitAssignStmt(node *AssignStmt) {
	fmt.Println("Visit Func Decl")
}
func (self *PrintVisitor) VisitReturnStmt(node *ReturnStmt) {
	fmt.Println("Visit Func Decl")
}
func (self *PrintVisitor) VisitBlockStmt(node *BlockStmt) {
	fmt.Println("Visit Func Decl")
}
func (self *PrintVisitor) VisitIfStmt(node *IfStmt) {
	fmt.Println("Visit Func Decl")
}
func (self *PrintVisitor) VisitForStmt(node *ForStmt) {
	fmt.Println("Visit Func Decl")
}

func (self *PrintVisitor) VisitFileAst(node *FileAst) {
	fmt.Println("Visit File: ")
}