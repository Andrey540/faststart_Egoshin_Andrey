package ast

import (
	"errors"

	"github.com/go-llvm/llvm"
)

type Scope struct {
	Outer   *Scope
	Objects map[string]*Object
}

func NewScope(outer *Scope) *Scope {
	const n = 4 // initial scope capacity
	return &Scope{outer, make(map[string]*Object, n)}
}

func (s *Scope) Lookup(name string) *Object {
	return s.Objects[name]
}

func (s *Scope) LookupDeep(name string) *Object {
	obj := s.Objects[name]
	if obj == nil {
		if s.Outer == nil {
			panic(errors.New("Can not find parameter with name: " + name))
		} else {
			return s.Outer.LookupDeep(name)
		}
	} else {
		return obj
	}
}

func (s *Scope) Insert(obj *Object) (alt *Object) {
	if alt = s.Objects[obj.Name]; alt == nil {
		s.Objects[obj.Name] = obj
	}
	return
}

type Object struct {
	Name string
	Kind ObjKind
	Decl interface{}
	Data interface{}
	Type interface{}
	Size interface{}
}

func (p *Object) GetFuncDecl() []Field {
	switch decl := p.Decl.(type) {
	case []Field:
		return decl
	default:
		panic(errors.New("Object has not func delc: " + p.Name))
	}
}

func (p *Object) IsArray() bool {
	return p.Kind == Arr
}

func (p *Object) IsFunction() bool {
	return p.Kind == Fun
}

func (p *Object) GetArraySize() uint64 {
	if !p.IsArray() && !p.IsFunction() {
		panic(errors.New("Object is not array: " + p.Name))
	}
	switch size := p.Size.(type) {
	case uint64:
		return size
	default:
		panic(errors.New("Array has not size: " + p.Name))
	}
}

func (p *Object) GetArrayType() *ArrayType {
	if !p.IsArray() {
		panic(errors.New("Object is not array: " + p.Name))
	}
	switch t := p.GetType().(type) {
	case *ArrayType:
		return t
	default:
		panic(errors.New("Object is not array: " + p.Name))
	}
}

func (p *Object) GetType() Expression {
	switch expr := p.Type.(type) {
	case Expression:
		return expr
	default:
		panic(errors.New("Object has not type: " + p.Name))
	}
}

func (p *Object) GetAlloca() llvm.Value {
	switch alloca := p.Data.(type) {
	case llvm.Value:
		return alloca
	default:
		panic(errors.New("Object has not alloca: " + p.Name))
	}
}

type ObjKind int

const (
	Bad ObjKind = iota
	Var
	Arr
	Fun
)

var objKindStrings = [...]string{
	Bad: "bad",
	Var: "var",
	Arr: "arr",
	Fun: "func",
}

func (p ObjKind) String() string {
	return objKindStrings[p]
}
