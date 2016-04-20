package parser

import (
	"ast"
	"io/ioutil"
)

func readSource(filename string) (string, error) {
	src, err := ioutil.ReadFile(filename)
	return string(src), err
}

func ParseFile(filename string) (f *ast.FileAst, err error) {
	text, err := readSource(filename)
	var p parser
	p.init(text)

	resultAst := p.parseFile();

	return resultAst, err
}
