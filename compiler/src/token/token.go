package token

import "strconv"

type Token struct {
	RowIndex int
	ColumnIndex int
	TokenType TokenType
	Value string
}

type Tokens []Token

type TokenType int

const (
	ILLEGAL TokenType = iota
	EOF
	COMMENT
	NEW_LINE

	RETURN
	VAR
	TYPE
	FUNC

	IDENTIFIER
	INT
	FLOAT
	STRING

	ADD
	SUB
	MUL
	QUO
	REM

	IF
	FOR
	ELSE
	BREAK
	CONTINUE

	LPAREN
	LBRACK
	LBRACE

	RPAREN
	RBRACK
	RBRACE

	SEMICOLON
	COLON

	COMMA // ,
	
	INT_NUMBER
	FLOAT_NUMBER
	LITERAL
	ASSIGNED
	EQUAL
	NOT_EQUAL
	NOT
	GREATE

	STRING_VALUE

	AND
	OR
	
	SIN
	COS
	SQRT
)

var tokens = [...]string{
	ILLEGAL: "ILLEGAL",

	EOF:     "EOF",
	COMMENT: "COMMENT",
	INT:    "INT",
	FLOAT:  "FLOAT",
	STRING: "STRING",
	NEW_LINE: "NEW_LINE",

	ADD: "+",
	SUB: "-",
	MUL: "*",
	QUO: "/",
	REM: "%",

	LPAREN: "(",
	LBRACK: "[",
	LBRACE: "{",

	RPAREN:    ")",
	RBRACK:    "]",
	RBRACE:    "}",
	SEMICOLON: ";",
	COLON:     ":",
	COMMA:     ",",
	
	INT_NUMBER:   "INT NUMBER",
	FLOAT_NUMBER: "FLOAT NUMBER",

	BREAK:    "BREAK",
	CONTINUE: "CONTINUE",

	IF:			 "IF",
	ELSE:        "ELSE",
	FOR:         "FOR",

	FUNC:   "FUNC",

	RETURN:    "RETURN",

	TYPE:   "TYPE",
	VAR:    "VAR",
	
	IDENTIFIER: "IDENTIFIER",
	ASSIGNED: "=",
	EQUAL: "==",
	NOT_EQUAL: "!=",
	NOT: "!",
	GREATE: ">",

	STRING_VALUE: "STRING VALUE",

	AND: "&&",
	OR: "||",
	
	SIN: "SIN",
	COS: "COS",
	SQRT: "SQRT",
}

func (tok TokenType) String() string {
	s := ""
	if 0 <= tok && tok < TokenType(len(tokens)) {
		s = tokens[tok]
	}
	if s == "" {
		s = "token(" + strconv.Itoa(int(tok)) + ")"
	}
	return s
}