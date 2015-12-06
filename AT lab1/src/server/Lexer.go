package main

import (
	"fmt"
	"regexp"
	"errors"
)

type Lexer struct {
	commentReg *regexp.Regexp
	intReg *regexp.Regexp
	floatReg *regexp.Regexp
	stringReg *regexp.Regexp
	
    addOpReg *regexp.Regexp
	subOpReg *regexp.Regexp
	mulOpReg *regexp.Regexp
	quoOpReg *regexp.Regexp
	remOpReg *regexp.Regexp
	
	lparenReg *regexp.Regexp
	lbrackReg *regexp.Regexp
	lbraceReg *regexp.Regexp
	
	rparenReg *regexp.Regexp
	rbrackReg *regexp.Regexp
	rbraceReg *regexp.Regexp
	semicolonReg *regexp.Regexp
	colonReg *regexp.Regexp
	
	breakReg *regexp.Regexp
	continueReg *regexp.Regexp
	
	ifReg *regexp.Regexp
	elseReg *regexp.Regexp
	forReg *regexp.Regexp
	
	funcReg *regexp.Regexp
	returnReg *regexp.Regexp
	
	typeReg *regexp.Regexp
	varReg *regexp.Regexp
	
    numberReg *regexp.Regexp
	whiteSpacesReg *regexp.Regexp
	rowIndex int
	columtIndex int
	tokens []string
}

func (self *Lexer) trim(expression string) string {	
	slice := self.whiteSpacesReg.FindStringIndex(expression)
	if slice != nil {
		self.columtIndex += slice[1]
		return expression[slice[1]:]
	}
	return expression
}

func (self *Lexer) parseTokenByExp(expressionSrc string, re regexp.Regexp, tokenType TokenType) (expression string, token Token) {	
	slice := re.FindStringIndex(expressionSrc)
	expression = expressionSrc
	if slice != nil {
		self.columtIndex += slice[1]
		token.columtIndex = self.columtIndex
		token.rowIndex = self.rowIndex
		token.tokenType = tokenType
		token.value = expression[slice[0]:slice[1]]
		expression = expression[slice[1]:]
		return expression, token
	}
	return expression, token
}

func (self *Lexer) parseToken(expressionSrc string) (expression string, token Token) {	
    expression = self.trim(expressionSrc)
	
	expression, token = self.parseTokenByExp(expression, *self.numberReg, NUMBER)
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.commentReg, COMMENT)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.intReg, INT)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.floatReg, FLOAT)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.stringReg, STRING)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.addOpReg, ADD)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.subOpReg, SUB)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.mulOpReg, MUL)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.quoOpReg, QUO)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.remOpReg, REM)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.lparenReg, LPAREN)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.lbrackReg, LBRACK)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.lbraceReg, LBRACE)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.rparenReg, RPAREN)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.rbrackReg, RBRACK)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.rbraceReg, RBRACE)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.semicolonReg, SEMICOLON)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.colonReg, COLON)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.breakReg, BREAK)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.continueReg, CONTINUE)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.ifReg, IF)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.elseReg, ELSE)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.forReg, FOR)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.funcReg, FUNC)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.returnReg, RETURN)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.typeReg, TYPE)
	}
	if token.tokenType == ILLEGAL {
		expression, token = self.parseTokenByExp(expression, *self.varReg, VAR)
	}
	if token.tokenType == ILLEGAL {
		panic(errors.New("unexpected token " + expression))
	}

	return expression, token
}

func (self *Lexer) parseTokens(expression string) {	
	self.rowIndex = 0
	self.columtIndex = 0
	
	self.commentReg = regexp.MustCompile(`^(comment)`)
	self.intReg = regexp.MustCompile(`^(int)`)
	self.floatReg = regexp.MustCompile(`^(float)`)
	self.stringReg = regexp.MustCompile(`^(string)`)
	
    self.addOpReg = regexp.MustCompile(`^(\+)`)
	self.subOpReg = regexp.MustCompile(`^(\-)`)
	self.mulOpReg = regexp.MustCompile(`^(\*)`)
	self.quoOpReg = regexp.MustCompile(`^(\/)`)
	self.remOpReg = regexp.MustCompile(`^(\%)`)
	
	self.lparenReg = regexp.MustCompile(`^(\()`)
	self.lbrackReg = regexp.MustCompile(`^(\[)`)
	self.lbraceReg = regexp.MustCompile(`^(\{)`)
	
	self.rparenReg = regexp.MustCompile(`^(\))`)
	self.rbrackReg = regexp.MustCompile(`^(\])`)
	self.rbraceReg = regexp.MustCompile(`^(\})`)
	self.semicolonReg = regexp.MustCompile(`^(;)`)
	self.colonReg = regexp.MustCompile(`^(:)`)
	
	self.breakReg = regexp.MustCompile(`^(break)`)
	self.continueReg = regexp.MustCompile(`^(continue)`)
	
	self.ifReg = regexp.MustCompile(`^(if)`)
	self.elseReg = regexp.MustCompile(`^(else)`)
	self.forReg = regexp.MustCompile(`^(for)`)
	
	self.funcReg = regexp.MustCompile(`^(func)`)
	self.returnReg = regexp.MustCompile(`^(return)`)
	
	self.typeReg = regexp.MustCompile(`^(type)`)
	self.varReg = regexp.MustCompile(`^(var)`)
	
	self.numberReg = regexp.MustCompile(`^(([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*)|([0-9]+))`)
	
	self.whiteSpacesReg = regexp.MustCompile(`^(\s+)`)

	var token Token
	var tokens []Token
	
	for expression != "" {
		expression, token = self.parseToken(expression)
		tokens = append(tokens, token)
	}
	
	fmt.Println(tokens)
}