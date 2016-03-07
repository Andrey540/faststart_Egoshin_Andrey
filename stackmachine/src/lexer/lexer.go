package lexer

import (
	"regexp"
	"token"
)

type Pattern struct { 
	expr *regexp.Regexp
	kind token.TokenType
}

type Error struct {
	RowIndex int
	ColumnIndex int
	Value string
}

type Lexer struct {
	patterns []Pattern
	whiteSpacesReg *regexp.Regexp
	absorbErrorReg *regexp.Regexp
	
	rowIndex int
	columtIndex int
	tokens []token.Token
	errors []Error
}

func (self *Lexer) trim(expression string) string {	
	slice := self.whiteSpacesReg.FindStringIndex(expression)
	if slice != nil {
		self.columtIndex += slice[1]
		return expression[slice[1]:]
	}
	return expression
}

func (self *Lexer) absorbError(expression string) (string, string) {	
	slice := self.absorbErrorReg.FindStringIndex(expression)
	if slice != nil {
		self.columtIndex += slice[1]
		return expression[slice[1]:], expression[slice[0]:slice[1]]
	}
	return expression, ""
}

func (self *Lexer) appendError(expression string) string {	
	var errorElem Error
	errorElem.ColumnIndex = self.columtIndex
	errorElem.RowIndex = self.rowIndex
	expression, errorElem.Value = self.absorbError(expression)
	self.errors = append(self.errors, errorElem)

	return expression
}

func (self *Lexer) parseTokenByExp(expressionSrc string, re regexp.Regexp, tokenType token.TokenType) (expression string, token token.Token) {
	slice := re.FindStringIndex(expressionSrc)
	expression = expressionSrc
	if slice != nil {
		token.ColumnIndex = self.columtIndex
		token.RowIndex = self.rowIndex
		token.TokenType = tokenType
		token.Value = expression[slice[0]:slice[1]]
		expression = expression[slice[1]:]
		self.columtIndex += slice[1]
		return expression, token
	}
	return expression, token
}

func (self *Lexer) parseToken(expressionSrc string) (expression string, tokenElem token.Token) {
    expression = self.trim(expressionSrc)

	for _, value := range self.patterns {
		expression, tokenElem = self.parseTokenByExp(expression, *value.expr, value.kind)
		if tokenElem.TokenType != token.ILLEGAL {
			break
		}
	}

	if tokenElem.TokenType == token.ILLEGAL {
		expression = self.appendError(expression)		
	}

	return expression, tokenElem
}

func (self *Lexer) ParseTokens(expression string) ([]token.Token, []Error) {
	self.rowIndex = 0
	self.columtIndex = 0

	pattern := Pattern {
		expr: regexp.MustCompile(`^((\/\*).*(\*\/))`),
		kind: token.COMMENT,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^((\").*(\"))`),
		kind: token.STRING_VALUE,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(int)`),
		kind: token.INT,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(float)`),
		kind: token.FLOAT,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(string)`),
		kind: token.STRING,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\+)`),
		kind: token.ADD,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\-)`),
		kind: token.SUB,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\*)`),
		kind: token.MUL,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\/)`),
		kind: token.QUO,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\%)`),
		kind: token.REM,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\()`),
		kind: token.LPAREN,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\[)`),
		kind: token.LBRACK,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\{)`),
		kind: token.LBRACE,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\))`),
		kind: token.RPAREN,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\])`),
		kind: token.RBRACK,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\})`),
		kind: token.RBRACE,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(;)`),
		kind: token.SEMICOLON,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(:)`),
		kind: token.COLON,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(,)`),
		kind: token.COMMA,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(break)`),
		kind: token.BREAK,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(continue)`),
		kind: token.CONTINUE,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(if)`),
		kind: token.IF,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(else)`),
		kind: token.ELSE,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(for)`),
		kind: token.FOR,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(func)`),
		kind: token.FUNC,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(return)`),
		kind: token.RETURN,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(type)`),
		kind: token.TYPE,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(var)`),
		kind: token.VAR,
	}
	self.patterns = append(self.patterns, pattern)
	
	pattern = Pattern {
		expr: regexp.MustCompile(`^(sin)`),
		kind: token.SIN,
	}
	self.patterns = append(self.patterns, pattern)
	
	pattern = Pattern {
		expr: regexp.MustCompile(`^(cos)`),
		kind: token.COS,
	}
	self.patterns = append(self.patterns, pattern)
	
	pattern = Pattern {
		expr: regexp.MustCompile(`^(sqrt)`),
		kind: token.SQRT,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\=\=)`),
		kind: token.EQUAL,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\=)`),
		kind: token.ASSIGNED,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*)|([0-9]+))f`),
		kind: token.FLOAT_NUMBER,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^([0-9]+)`),
		kind: token.INT_NUMBER,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^([a-zA-Z]+[a-zA-Z0-9]*)`),
		kind: token.IDENTIFIER,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\!\=)`),
		kind: token.NOT_EQUAL,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\!)`),
		kind: token.NOT,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\>)`),
		kind: token.GREATE,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\&\&)`),
		kind: token.AND,
	}
	self.patterns = append(self.patterns, pattern)

	pattern = Pattern {
		expr: regexp.MustCompile(`^(\|\|)`),
		kind: token.OR,
	}
	self.patterns = append(self.patterns, pattern)	

	self.whiteSpacesReg = regexp.MustCompile(`^(\s+)`)
	self.absorbErrorReg = regexp.MustCompile(`^(.[^\s]+)`)

	var t token.Token
	for expression != "" {
		expression, t = self.parseToken(expression)
		self.tokens = append(self.tokens, t)
		expression = self.trim(expression)
	}

	self.tokens = append(self.tokens, token.Token{
		TokenType: token.EOF,
	})
	
	return self.tokens, self.errors
}