// Copyright 2011 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

// based off of Appendix A from http://dinosaur.compilertools.net/yacc/

%{

package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"lexer"
	"token"
	"ast"
	"bytes"
	"strconv"
)

var regs = make(map[string]ast.Expression)
var base ast.Expression

var mainResult ast.FileAst

var identifiers []ast.Ident
var blockstmts []ast.BlockStmt

%}

// fields inside this union end up as the fields in a structure known
// as ${PREFIX}SymType, of which a reference is passed to the lexer.
%union{
	val int
	expression ast.Expression
	expression_list []ast.Expression
	declaration ast.Declaration
	statement ast.Statement
	statement_list ast.BlockStmt
	statement_block int
	token token.Token
	file ast.FileAst
	field ast.Field
	field_list []ast.Field	
	identifier int
}

// any non-terminal which returns a value needs a type, which is
// really a field name in the above union struct
%type <token> enumerable
%type <expression> expr number type
%type <expression_list> expr_list
%type <declaration> declaration
%type <identifier> identifier
%type <file> file
%type <statement> statement
%type <statement_list> statement_list
%type <statement_block> statement_block
%type <field> field
%type <field_list> field_list
	
%token <token> EOF
%token <token> LBRACE RBRACE IF ELSE FOR RETURN FUNC COMMENT LBRACK RBRACK COMMA
%token <token> INT_NUMBER FLOAT_NUMBER STRING_VALUE INT FLOAT STRING NEW_LINE VAR ASSIGNED IDENTIFIER
%token <token> ADD SUB MUL QUO REM SIN COS SQRT LPAREN RPAREN
%token <token> EQUAL NOT_EQUAL GREATE AND OR

%left ASSIGNED EQUAL NOT_EQUAL GREATE AND OR
%left ADD  SUB
%left MUL  QUO  REM
%left UMINUS      /*  supplies  precedence  for  unary  minus  */
%left SIN COS SQRT

%%

file    : declaration
		{
			fmt.Println("file begin")
			$$ = ast.FileAst{Decls: []ast.Declaration{$1}}
		}
	|	file declaration
		{
			fmt.Println("add decl to list")
			$1.Decls = append($1.Decls, $2)
			$$ = $1
		}
	|    file EOF
		{
			fmt.Println("EOF")
			mainResult = $1
		}
	;
statement_block	: LBRACE NEW_LINE statement_list RBRACE
		{
			fmt.Println("init stmt block")
			blockstmts = append(blockstmts, $3)
			$$ = len(blockstmts) - 1
		}
	;	
	
statement_list : statement
		{
			fmt.Println("list statement begin")
			fmt.Println($1)
			$$ = ast.BlockStmt{List: []ast.Statement{$1}}
		}
	|     statement_list statement
		{
			fmt.Println("add stmt to list")
			$1.List = append($1.List, $2)
			$$ = $1
		}	
	;
statement	: declaration
		{
			fmt.Println("decl --> stmt")
			fmt.Println($1)
			$$ = &ast.DeclStmt{Decl: $1}
		}	
	|   expr ASSIGNED expr NEW_LINE
		{
			fmt.Println("assigned --> stmt")			
			$$ = &ast.AssignStmt {
				Ident: $1,
				Op: $2.TokenType,
				X: $3,			
			}
			
		}
	|    COMMENT
		{
			fmt.Println("comment")			
			$$ = &ast.EmptyStmt {}
		}
	|    RETURN expr
		{
			// conflict
			fmt.Println("return stmt")			
			$$ = &ast.ReturnStmt {
				X: $2,			
			}
			
		}
	|	IF expr statement_block ELSE statement_block
		{
			fmt.Println("if stmt with else")
			$$ = &ast.IfStmt {
				Cond: $2,
				Body: &blockstmts[$3],
				Else: &blockstmts[$5],
			}
		}
	|	IF expr statement_block
		{
			fmt.Println("if stmt")
			$$ = &ast.IfStmt {
				Cond: $2,
				Body: &blockstmts[$3],
			}
		}
	|	FOR expr statement_block
		{
			fmt.Println("for stmt")
			$$ = &ast.ForStmt {
				X: $2,
				Body: &blockstmts[$3],
			}
		}
	|	statement NEW_LINE
		{
			fmt.Println("stmt + new line")
			$$ = $1
		}
	;

declaration : VAR identifier type		{
			fmt.Println("var")
			$$ = &ast.VarDecl {
				Name: &identifiers[$2],
				Type: $3,
			}
		}
	|    FUNC identifier LPAREN RPAREN type statement_block
		{
			fmt.Println("func")
			$$ = &ast.FuncDecl {
				Name: &identifiers[$2],
				RetType: $5,
				Body: &blockstmts[$6],
			}
		}
	|    FUNC identifier LPAREN field_list RPAREN type statement_block
		{
			fmt.Println("func")
			$$ = &ast.FuncDecl {
				Name: &identifiers[$2],
				Params: $4,
				RetType: $6,
				Body: &blockstmts[$7],
			}
		}
	|	declaration NEW_LINE
		{
			fmt.Println("decl new line")
			$$ = $1
		}	
	;	
	
field_list  : field
		{
			$$ = []ast.Field{$1}
		}
	|    field_list COMMA field
		{
			$$ = append($1, $3)
		}
	;
	
field   :  identifier type
		{
			fmt.Println("field")
			$$ = ast.Field {
				Name: &identifiers[$1],
				Type: $2,
			}
		}
	;
	
expr_list  :    expr
		{
			$$ = []ast.Expression{$1}
		}
	|    expr_list COMMA expr
		{
			$$ = append($1, $3)
		}
	;
	
expr	:    LPAREN expr RPAREN
		{ 
			fmt.Printf("expr <- LPAREN expr RPAREN\n")
			$$ = $2 
		}
	|    identifier LBRACK expr RBRACK
		{ 
			$$ = &ast.BinaryExpr {
				X: &identifiers[$1],
				OpT: $2,
				Y: $3,
			}
		}
	|    identifier LPAREN expr_list RPAREN
		{ 
		// conflict
			$$ = &ast.CallExpr {
				Fun: &identifiers[$1],
				Args: $3,
			}
		}
	|    identifier LPAREN RPAREN
		{ 
			$$ = &ast.CallExpr {
				Fun: &identifiers[$1],
			}
		}
	|    expr ADD expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
		}
	|    expr SUB expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
		}
	|    expr MUL expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
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
	|    expr EQUAL expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
		}
	|    expr NOT_EQUAL expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
		}
	|    expr GREATE expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
		}	
	|    expr AND expr
		{ 
			fmt.Println($2.Value)
			$$ = &ast.BinaryExpr {
				X: $1,
				OpT: $2,
				Y: $3,
			}
		}
	|    expr OR expr
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
		}
	|    identifier
		{
			fmt.Println("identifier -> expr")
			$$ = &identifiers[$1]
		}
	|    number
		{
		    fmt.Println("expr <- number")
			$$ = $1
		}
	;
	
identifier : IDENTIFIER
		{
			fmt.Println("identifier")			
			ident := ast.Ident{
				Name: $1.Value,
				T: $1,
			}
			identifiers = append(identifiers, ident)
			$$ = len(identifiers) - 1
		}
	;
	
type    : INT
		{
			fmt.Println($1.Value)
			$$ = &ast.BasicLit{T: $1}
		}
	| 	 FLOAT
		{
			fmt.Println($1.Value)
			$$ = &ast.BasicLit{T: $1}
		}
	|    STRING
		{
			fmt.Println($1.Value)
			$$ = &ast.BasicLit{T: $1}
		}
	|	 LBRACK RBRACK type
		{
			fmt.Println("array")
			$$ = &ast.ArrayType {
				Index: -1,
				At: $3,
			}
		}
	|	 LBRACK enumerable RBRACK type
		{
			value, err := strconv.Atoi($2.Value)
			if err != nil {
				panic(err)
			}
			fmt.Println("array")
			$$ = &ast.ArrayType {
				Index: value,
				At: $4,
			}
		}
	;

number	:   enumerable
		{
			fmt.Println($1.Value)
			$$ = &ast.BasicLit{T: $1}
		}
	| 		FLOAT_NUMBER
		{
			fmt.Println($1.Value)
			$$ = &ast.BasicLit{T: $1}
		}
	| 		STRING_VALUE
		{
			fmt.Println($1.Value)
			$$ = &ast.BasicLit{T: $1}
		}
	;
	
enumerable : INT_NUMBER
		{
			$$ = $1
		}
	;

%%      /*  start  of  programs  */

type CalcLex struct {
	tokens []token.Token
	tokenMap map[int]int
	statement ast.Expression
	pos int
}


func (l *CalcLex) Lex(lval *CalcSymType) int {	
	if l.pos == len(l.tokens) {
		return 0
	}
	var c token.Token = l.tokens[l.pos]
	l.pos += 1	
	lval.token = c	
	
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
	tokenMap[int(token.INT)] = INT
	tokenMap[int(token.FLOAT)] = FLOAT
	tokenMap[int(token.STRING)] = STRING
	tokenMap[int(token.VAR)] = VAR
	tokenMap[int(token.NEW_LINE)] = NEW_LINE
	tokenMap[int(token.LBRACE)] = LBRACE
	tokenMap[int(token.RBRACE)] = RBRACE
	tokenMap[int(token.IF)] = IF
	tokenMap[int(token.ELSE)] = ELSE
	tokenMap[int(token.FOR)] = FOR
	tokenMap[int(token.RETURN)] = RETURN
	tokenMap[int(token.FUNC)] = FUNC
	tokenMap[int(token.COMMENT)] = COMMENT
	tokenMap[int(token.LBRACK)] = LBRACK
	tokenMap[int(token.RBRACK)] = RBRACK
	tokenMap[int(token.COMMA)] = COMMA
	tokenMap[int(token.EQUAL)] = EQUAL
	tokenMap[int(token.NOT_EQUAL)] = NOT_EQUAL
	tokenMap[int(token.GREATE)] = GREATE
	tokenMap[int(token.STRING_VALUE)] = STRING_VALUE
	tokenMap[int(token.AND)] = AND
	tokenMap[int(token.OR)] = OR
	
	return tokenMap
}

func main() {	
	if buffer, ok := readFile(); ok {
		fmt.Println(buffer)
		lexerObj := new(lexer.Lexer)
		tokensParsed, errors := lexerObj.ParseTokens(buffer)
		fmt.Println(tokensParsed)
		if len(errors) > 0 {
			panic("Unexpected tokens")
		}
		tokenMapPrepared := prepareTokenMap()
		CalcParse(&CalcLex{tokens: tokensParsed, tokenMap: tokenMapPrepared})
		scopeCreator := new(ast.ScopeCreatorVisitor)
		mainResult.Accept(scopeCreator)
		astChecker := new(ast.AstCheckerVisitor)
		mainResult.Accept(astChecker)
	} else {
		fmt.Printf("Error reading file")
	}
}

func readline(fi *bufio.Reader) (string, bool) {
	s, err := fi.ReadString('\n')
	if err != nil {
		return "", false
	}
	return s, true
}

func readFile() (string, bool) {
	buf := bytes.NewBuffer(nil)
	f, err := os.Open("input.txt")
	if err != nil {
		return "", false
	}
    io.Copy(buf, f)
    f.Close()
	return string(buf.Bytes()), true
}