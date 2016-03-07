package ast

type Object struct {
	Name string
	Kind ObjKind
	Decl interface{}
	Data interface{}
	Type interface{}
}

type ObjKind int

const (
	Bad ObjKind = iota
	Var
	Fun
)

var objKindStrings = [...]string{
	Bad: "bad",
	Var: "var",
	Fun: "func",
}

func (p ObjKind) String() string {
	return objKindStrings[p]
}
