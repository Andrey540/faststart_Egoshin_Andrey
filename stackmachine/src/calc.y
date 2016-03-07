// Copyright 2011 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

// based off of Appendix A from http://dinosaur.compilertools.net/yacc/

%{

package main

import (
	"bufio"
	"fmt"
	"os"
	"lexer"
	"token"
	"ast"
	"stackmachine"
	"bytes"
)

var regs = make(map[string]ast.Expression)
var base ast.Expression

var mainResult ast.Expression
var stackMachineExpr string

%}

// fields inside this union end up as the fields in a structure known
// as ${PREFIX}SymType, of which a reference is passed to the lexer.
%union{
	val int
	nodeAst ast.Expression
	token token.Token
	lex CalcLex
}

// any non-terminal which returns a value needs a type, which is
// really a field name in the above union struct
%type <nodeAst> expr number statement

%token <lex> EOF

// same for terminals
%token <token> INT_NUMBER FLOAT_NUMBER

// same for terminals
%token <token> ADD SUB MUL QUO REM SIN COS SQRT LPAREN RPAREN ASSIGNED IDENTIFIER

%left ADD  SUB
%left MUL  QUO  REM
%left UMINUS      /*  supplies  precedence  for  unary  minus  */
%left SIN COS SQRT

%%

list	: /* empty */
	| statement
	;

statement	:    expr
		{
			fmt.Println("end expr")
			$$ = $1
		}
	|    IDENTIFIER ASSIGNED expr
		{
			regs[$1.Value] = $3
		}
	|	expr EOF
		{
			fmt.Println("EOF")
			mainResult = $1
		}
	;


expr	:    LPAREN expr RPAREN
		{ 
			fmt.Printf("expr <- LPAREN expr RPAREN\n")
			$$ = $2 
		}
	|    expr ADD expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
			stackMachineExpr += "add\n"
		}
	|    expr SUB expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
			stackMachineExpr += "sub\n"
		}
	|    expr MUL expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
			stackMachineExpr += "mul\n"
		}
	|    expr QUO expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
		}
	|    expr REM expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
		}
	|    SIN LPAREN expr RPAREN
		{
			fmt.Println($1.Value)
			$$ = &ast.UnaryExpr{
				X: $3,
				OpT: $1,
			}			
	     }
	|    COS LPAREN expr RPAREN
		{
			fmt.Println($1.Value)
			$$ = &ast.UnaryExpr{
				X: $3,
				OpT: $1,
			}			
	     }
	|    SQRT LPAREN expr RPAREN
	     {
			fmt.Println($1.Value)
			$$ = &ast.UnaryExpr{
				X: $3,
				OpT: $1,
			}			
	     }
	|    SUB  expr        %prec  UMINUS
		{
			fmt.Println($1.Value)
			$$ = &ast.UnaryExpr{
				X: $2,
				OpT: $1,
			}
			stackMachineExpr += "div\n"
		}
	|    IDENTIFIER
		{
			$$ = regs[$1.Value]
		}
	|    number
		{
		    fmt.Printf("expr <- number\n")
			$$ = $1
		}
	;

number	:   INT_NUMBER
		{
			fmt.Println($1.Value)
			$$ = &ast.BasicLit{T: $1}
			stackMachineExpr += "push " + $1.Value + "\n "
		}
	| 		FLOAT_NUMBER
		{
			fmt.Println($1.Value)
			$$ = &ast.BasicLit{T: $1}
		}
	;

%%      /*  start  of  programs  */

type CalcLex struct {
	tokens []token.Token
	tokenMap map[int]int
	nodeAst ast.Expression
	pos int
}


func (l *CalcLex) Lex(lval *CalcSymType) int {	
	if l.pos == len(l.tokens) {
		return 0
	}
	var c token.Token = l.tokens[l.pos]
	l.pos += 1
	
	if (lval.token.TokenType == token.EOF) {
		lval.lex = *l
	} else {
		lval.token = c
	}	
	return int(l.tokenMap[int(c.TokenType)])
}

func (l *CalcLex) Error(s string) {
	fmt.Printf("syntax error: %s\n", s)
}

func prepareTokenMap() map[int]int {
	var tokenMap map[int]int
	tokenMap = make(map[int]int)

	tokenMap[int(token.ADD)] = ADD
	tokenMap[int(token.SUB)] = SUB
	tokenMap[int(token.MUL)] = MUL
	tokenMap[int(token.QUO)] = QUO
	tokenMap[int(token.REM)] = REM
	tokenMap[int(token.SIN)] = SIN
	tokenMap[int(token.COS)] = COS
	tokenMap[int(token.SQRT)] = SQRT
	tokenMap[int(token.EOF)] = EOF
	tokenMap[int(token.LPAREN)] = LPAREN
	tokenMap[int(token.RPAREN)] = RPAREN
	tokenMap[int(token.ASSIGNED)] = ASSIGNED
	tokenMap[int(token.INT_NUMBER)] = INT_NUMBER
	tokenMap[int(token.FLOAT_NUMBER)] = FLOAT_NUMBER
	tokenMap[int(token.IDENTIFIER)] = IDENTIFIER
	
	return tokenMap
}

func main() {
	fi := bufio.NewReader(os.Stdin)	

	for {
		var eqn string
		var ok bool
		stackMachineExpr = "";
	
		fmt.Printf("equation: ")
		if eqn, ok = readline(fi); ok {
			lexerObj := new(lexer.Lexer)
			tokensParsed, errors := lexerObj.ParseTokens(eqn)
			if len(errors) > 0 {
				panic("Unexpected tokens")
			}
			tokenMapPrepared := prepareTokenMap()
			CalcParse(&CalcLex{tokens: tokensParsed, tokenMap: tokenMapPrepared})
			fmt.Println(mainResult)
		} else {
			break
		}
		buffer := bytes.NewBufferString(stackMachineExpr)
		fi = bufio.NewReader(buffer)
		stackmachineObj := new(stackmachine.StackMachine)
		stackmachineObj.Execute(fi);
		stackmachineObj.PrintStackAll();
	}		
}

func readline(fi *bufio.Reader) (string, bool) {
	s, err := fi.ReadString('\n')
	if err != nil {
		return "", false
	}
	return s, true
}