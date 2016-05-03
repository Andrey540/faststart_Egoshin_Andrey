package ast

import (
	"fmt"
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

func (s *Scope) LookupAll(name string) *Object {
	obj :=  s.Objects[name]
	if obj == nil {
		if s.Outer == nil {
			panic(fmt.Sprintf("Can not find parameter with name " + name))
		} else {
			return s.Outer.LookupAll(name)
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
}

func (p *Object) GetFuncDecl() []Field {
	switch decl := p.Decl.(type) {
		case []Field:
			return decl
		default:
			panic(fmt.Sprintf("Object has not func delc"))
	}
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
