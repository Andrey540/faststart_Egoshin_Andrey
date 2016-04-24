package ast

import (
	"token"
)

type NodeAst interface {
	astNode()
	Accept(v Visitor)
}

type File interface {
	astNode()
	Accept(v Visitor)
}

type Declaration interface {
	NodeAst
	declNode()
}

type Statement interface {
	NodeAst
	stmtNode()
}

type Expression interface {
	NodeAst
	exprNode()
}

// Expressions
type (
	BadExpr struct {
		Msg string
	}

	BasicLit struct {
		T token.Token
	}

	Ident struct {
		Name string
		T token.Token
		Obj *Object
	}

	UnaryExpr struct {
		X Expression
		Op token.TokenType
		OpT token.Token
	}

	BinaryExpr struct {
		X Expression
		Op token.TokenType
		OpT token.Token
		Y Expression
	}

	ArrayType struct {
		Index int
		At Expression  // base_type
	}
)

func (p *BadExpr) astNode() {}
func (p *BasicLit) astNode() {}
func (p *Ident) astNode() {}
func (p *UnaryExpr) astNode() {}
func (p *BinaryExpr) astNode() {}
func (p *ArrayType) astNode() {}

func (p *BadExpr) exprNode() {}
func (p *BasicLit) exprNode() {}
func (p *Ident) exprNode() {}
func (p *UnaryExpr) exprNode() {}
func (p *BinaryExpr) exprNode() {}
func (p *ArrayType) exprNode() {}

// Declarations
type (
	VarDecl struct {
		Name *Ident
		Type Expression
	}

	FuncDecl struct {
		Name *Ident
		Params []Field
		RetType Expression
		Body *BlockStmt
	}
)

type Field struct {
	Name *Ident
	Type Expression
}

func (p *VarDecl) astNode() {}
func (p *FuncDecl) astNode() {}

func (p *VarDecl) declNode() {}
func (p *FuncDecl) declNode() {}


// Statements
type (
	DeclStmt struct {
		Decl Declaration
	}

	EmptyStmt struct {}

	ExprStmt struct {
		X Expression
	}

	AssignStmt struct {
		Ident Expression
		Op token.TokenType
		X Expression
	}

	ReturnStmt struct {
		X Expression
	}

	BlockStmt struct {
		List []Statement
	}

	IfStmt struct {
		Cond Expression
		Body *BlockStmt
		Else *BlockStmt
	}

	ForStmt struct {
		X Expression
		Body *BlockStmt
	}
)

func (p *DeclStmt) astNode() {}
func (p *EmptyStmt) astNode() {}
func (p *ExprStmt) astNode() {}
func (p *AssignStmt) astNode() {}
func (p *ReturnStmt) astNode() {}
func (p *BlockStmt) astNode() {}
func (p *IfStmt) astNode() {}
func (p *ForStmt) astNode() {}

func (p *DeclStmt) stmtNode() {}
func (p *EmptyStmt) stmtNode() {}
func (p *ExprStmt) stmtNode() {}
func (p *AssignStmt) stmtNode() {}
func (p *ReturnStmt) stmtNode() {}
func (p *BlockStmt) stmtNode() {}
func (p *IfStmt) stmtNode() {}
func (p *ForStmt) stmtNode() {}

// File
type FileAst struct {
	Decls []Declaration
	Name string
}

func (p *FileAst) astNode() {}

func (p *FileAst) Accept(v Visitor) {
	v.VisitFileAst(p)
}

// accept implementations

func (p *BadExpr) Accept(v Visitor) {
	v.VisitBadExpr(p)
}
func (p *BasicLit) Accept(v Visitor) {
	v.VisitBasicLit(p)
}
func (p *Ident) Accept(v Visitor) {
	v.VisitIdent(p)
}
func (p *UnaryExpr) Accept(v Visitor) {
	v.VisitUnaryExpr(p)
}
func (p *BinaryExpr) Accept(v Visitor) {
	v.VisitBinaryExpr(p)
}
func (p *ArrayType) Accept(v Visitor) {
	v.VisitArrayType(p)
}

func (p *VarDecl) Accept(v Visitor) {
	v.VisitVarDecl(p)
}
func (p *FuncDecl) Accept(v Visitor) {
	v.VisitFunc(p)
}

func (p *DeclStmt) Accept(v Visitor) {
	v.VisitDeclStmt(p)
}
func (p *EmptyStmt) Accept(v Visitor) {
	v.VisitEmptyStmt(p)
}
func (p *ExprStmt) Accept(v Visitor) {
	v.VisitExprStmt(p)
}
func (p *AssignStmt) Accept(v Visitor) {
	v.VisitAssignStmt(p)
}
func (p *ReturnStmt) Accept(v Visitor) {
	v.VisitReturnStmt(p)
}
func (p *BlockStmt) Accept(v Visitor) {
	v.VisitBlockStmt(p)
}
func (p *IfStmt) Accept(v Visitor) {
	v.VisitIfStmt(p)
}
func (p *ForStmt) Accept(v Visitor) {
	v.VisitForStmt(p)
}