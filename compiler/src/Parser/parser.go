package parser

import (
	"token"
	"lexer"
	"ast"
	"fmt"
)

type parser struct {
	currentToken token.Token
	tokens token.Tokens
	index int
}

func (p *parser) next() {
	if len(p.tokens) == p.index {
		p.currentToken = token.Token{
			TokenType: token.EOF,
		}
	}
	p.currentToken = p.tokens[p.index]
	p.index++
}

func (p *parser) init(source string) {
	lexerObj := new(lexer.Lexer)
	tokens, _ := lexerObj.ParseTokens(source)
	p.tokens = tokens
	p.index = 0
}

func (p *parser) parseIdentifier() *ast.Ident {
	return &ast.Ident{
		Name: p.currentToken.Value,
	}
}

func (p *parser) parseVarDeclaration() *ast.VarDecl {
	return &ast.VarDecl{

	}
}

func (p *parser) parseFuncDeclaration() *ast.FuncDecl {
	return &ast.FuncDecl{

	}
}

func (p *parser) parseDeclaration() ast.Declaration {
	switch p.currentToken.TokenType {
	case token.VAR:

	case token.FUNC:

	}

	return &ast.VarDecl{}
}

func (p *parser) parseFile() *ast.FileAst {

	var decls []ast.Declaration
	fmt.Println("parser.parseFile() exec")
	for p.currentToken.TokenType != token.EOF {
		decls = append(decls, p.parseDeclaration())
		p.next()
	}

	return &ast.FileAst{
		Decls: decls,
	}
}