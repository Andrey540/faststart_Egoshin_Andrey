package main

import "strconv"

type Token struct {
	rowIndex int
	columtIndex int
	tokenType TokenType
	value string
}

type TokenType int

const (
	ILLEGAL TokenType = iota
	EOF
	COMMENT

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
	
	NUMBER
)

var tokens = [...]string{
	ILLEGAL: "ILLEGAL",

	EOF:     "EOF",
	COMMENT: "COMMENT",
	INT:    "INT",
	FLOAT:  "FLOAT",
	STRING: "STRING",

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
	
	NUMBER:   "number",

	BREAK:    "break",
	CONTINUE: "continue",

	IF:			 "if",
	ELSE:        "else",
	FOR:         "for",

	FUNC:   "func",

	RETURN:    "return",

	TYPE:   "type",
	VAR:    "var",
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