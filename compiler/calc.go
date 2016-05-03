//line calc.y:7

package main

import __yyfmt__ "fmt"

//line calc.y:10
import (
	"ast"
	"bufio"
	"bytes"
	"fmt"
	"io"
	"lexer"
	"os"
	"strconv"
	"token"
)

var regs = make(map[string]ast.Expression)
var base ast.Expression

var mainResult ast.FileAst

var identifiers []ast.Ident
var blockstmts []ast.BlockStmt

//line calc.y:35
type CalcSymType struct {
	yys             int
	val             int
	expression      ast.Expression
	expression_list []ast.Expression
	declaration     ast.Declaration
	statement       ast.Statement
	statement_list  ast.BlockStmt
	statement_block int
	token           token.Token
	file            ast.FileAst
	field           ast.Field
	field_list      []ast.Field
	identifier      int
}

const EOF = 57346
const LBRACE = 57347
const RBRACE = 57348
const IF = 57349
const ELSE = 57350
const FOR = 57351
const RETURN = 57352
const FUNC = 57353
const COMMENT = 57354
const LBRACK = 57355
const RBRACK = 57356
const COMMA = 57357
const INT_NUMBER = 57358
const FLOAT_NUMBER = 57359
const INT = 57360
const FLOAT = 57361
const STRING = 57362
const NEW_LINE = 57363
const VAR = 57364
const ASSIGNED = 57365
const IDENTIFIER = 57366
const ADD = 57367
const SUB = 57368
const MUL = 57369
const QUO = 57370
const REM = 57371
const SIN = 57372
const COS = 57373
const SQRT = 57374
const LPAREN = 57375
const RPAREN = 57376
const UMINUS = 57377

var CalcToknames = []string{
	"EOF",
	"LBRACE",
	"RBRACE",
	"IF",
	"ELSE",
	"FOR",
	"RETURN",
	"FUNC",
	"COMMENT",
	"LBRACK",
	"RBRACK",
	"COMMA",
	"INT_NUMBER",
	"FLOAT_NUMBER",
	"INT",
	"FLOAT",
	"STRING",
	"NEW_LINE",
	"VAR",
	"ASSIGNED",
	"IDENTIFIER",
	"ADD",
	"SUB",
	"MUL",
	"QUO",
	"REM",
	"SIN",
	"COS",
	"SQRT",
	"LPAREN",
	"RPAREN",
	"UMINUS",
}
var CalcStatenames = []string{}

const CalcEofCode = 1
const CalcErrCode = 2
const CalcMaxDepth = 200

//line calc.y:423

/*  start  of  programs  */

type CalcLex struct {
	tokens    []token.Token
	tokenMap  map[int]int
	statement ast.Expression
	pos       int
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
		fmt.Println(mainResult)
		fmt.Println(identifiers)
		visitor := new(ast.ScopeCreatorVisitor)
		mainResult.Accept(visitor)
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

//line yacctab:1
var CalcExca = []int{
	-1, 1,
	1, -1,
	-2, 0,
}

const CalcNprod = 48
const CalcPrivate = 57344

var CalcTokenNames []string
var CalcStates []string

const CalcLast = 195

var CalcAct = []int{

	40, 31, 54, 43, 38, 44, 42, 4, 41, 9,
	67, 71, 19, 53, 70, 92, 69, 28, 3, 20,
	9, 16, 50, 19, 53, 9, 47, 48, 49, 45,
	68, 9, 56, 50, 93, 36, 27, 47, 48, 49,
	45, 84, 55, 63, 64, 65, 66, 7, 89, 22,
	35, 72, 58, 59, 60, 61, 62, 25, 73, 74,
	75, 76, 77, 78, 90, 32, 79, 80, 82, 85,
	86, 87, 88, 58, 59, 60, 61, 62, 34, 43,
	4, 44, 42, 4, 41, 60, 61, 62, 19, 53,
	6, 3, 97, 98, 3, 21, 9, 4, 50, 19,
	53, 37, 47, 48, 49, 45, 46, 9, 3, 50,
	8, 10, 1, 47, 48, 49, 45, 58, 59, 60,
	61, 62, 17, 23, 19, 83, 96, 58, 59, 60,
	61, 62, 39, 2, 5, 23, 95, 58, 59, 60,
	61, 62, 51, 0, 0, 0, 94, 58, 59, 60,
	61, 62, 91, 32, 52, 57, 81, 58, 59, 60,
	61, 62, 11, 58, 59, 60, 61, 62, 0, 0,
	18, 0, 0, 58, 59, 60, 61, 62, 0, 0,
	24, 0, 0, 26, 0, 0, 29, 15, 30, 0,
	33, 0, 12, 13, 14,
}
var CalcPact = []int{

	69, 86, 26, 1, 1, 26, -1000, -1000, 174, -1000,
	-12, -1000, -1000, -1000, -1000, 108, -15, 174, 43, -1000,
	174, 2, -1000, 174, -1000, 174, 60, 174, 1, -1000,
	-1000, -1000, 29, 60, -1000, 72, -1000, -4, 11, 26,
	132, -1000, 83, 83, 83, 83, -3, -17, -19, -22,
	83, -1000, -1000, -1000, -1000, 11, -1000, 83, 83, 83,
	83, 83, 83, 48, 148, 148, 122, 83, 7, 83,
	83, 83, -1000, 27, 58, 58, -1000, -1000, -1000, 56,
	-1000, -1000, 138, 0, -1000, 48, 112, 102, 92, -1000,
	60, -1000, 83, -1000, -1000, -1000, -1000, -1000, 48,
}
var CalcPgo = []int{

	0, 154, 0, 142, 162, 125, 132, 106, 112, 4,
	101, 1, 49, 95,
}
var CalcR1 = []int{

	0, 8, 8, 8, 11, 10, 10, 9, 9, 9,
	9, 9, 9, 9, 9, 6, 6, 6, 6, 13,
	13, 12, 5, 5, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 7,
	4, 4, 4, 4, 4, 3, 3, 1,
}
var CalcR2 = []int{

	0, 1, 2, 2, 4, 1, 2, 1, 4, 1,
	2, 5, 3, 3, 2, 3, 6, 7, 2, 1,
	3, 2, 1, 3, 3, 4, 4, 3, 3, 3,
	3, 3, 3, 4, 4, 4, 2, 1, 1, 1,
	1, 1, 1, 3, 4, 1, 1, 1,
}
var CalcChk = []int{

	-1000, -8, -6, 22, 11, -6, 4, 21, -7, 24,
	-7, -4, 18, 19, 20, 13, 33, 14, -1, 16,
	34, -13, -12, -7, -4, 14, -4, 34, 15, -4,
	-4, -11, 5, -4, -12, 21, -11, -10, -9, -6,
	-2, 12, 10, 7, 9, 33, -7, 30, 31, 32,
	26, -3, -1, 17, 6, -9, 21, 23, 25, 26,
	27, 28, 29, -2, -2, -2, -2, 13, 33, 33,
	33, 33, -2, -2, -2, -2, -2, -2, -2, -11,
	-11, 34, -2, -5, 34, -2, -2, -2, -2, 21,
	8, 14, 15, 34, 34, 34, 34, -11, -2,
}
var CalcDef = []int{

	0, -2, 1, 0, 0, 2, 3, 18, 0, 39,
	0, 15, 40, 41, 42, 0, 0, 0, 0, 47,
	0, 0, 19, 0, 43, 0, 0, 0, 0, 21,
	44, 16, 0, 0, 20, 0, 17, 0, 5, 7,
	0, 9, 0, 0, 0, 0, 37, 0, 0, 0,
	0, 38, 45, 46, 4, 6, 14, 0, 0, 0,
	0, 0, 0, 10, 0, 0, 0, 0, 0, 0,
	0, 0, 36, 0, 28, 29, 30, 31, 32, 12,
	13, 24, 0, 0, 27, 22, 0, 0, 0, 8,
	0, 25, 0, 26, 33, 34, 35, 11, 23,
}
var CalcTok1 = []int{

	1,
}
var CalcTok2 = []int{

	2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
	12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
	22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35,
}
var CalcTok3 = []int{
	0,
}

//line yaccpar:1

/*	parser for yacc output	*/

var CalcDebug = 0

type CalcLexer interface {
	Lex(lval *CalcSymType) int
	Error(s string)
}

const CalcFlag = -1000

func CalcTokname(c int) string {
	// 4 is TOKSTART above
	if c >= 4 && c-4 < len(CalcToknames) {
		if CalcToknames[c-4] != "" {
			return CalcToknames[c-4]
		}
	}
	return __yyfmt__.Sprintf("tok-%v", c)
}

func CalcStatname(s int) string {
	if s >= 0 && s < len(CalcStatenames) {
		if CalcStatenames[s] != "" {
			return CalcStatenames[s]
		}
	}
	return __yyfmt__.Sprintf("state-%v", s)
}

func Calclex1(lex CalcLexer, lval *CalcSymType) int {
	c := 0
	char := lex.Lex(lval)
	if char <= 0 {
		c = CalcTok1[0]
		goto out
	}
	if char < len(CalcTok1) {
		c = CalcTok1[char]
		goto out
	}
	if char >= CalcPrivate {
		if char < CalcPrivate+len(CalcTok2) {
			c = CalcTok2[char-CalcPrivate]
			goto out
		}
	}
	for i := 0; i < len(CalcTok3); i += 2 {
		c = CalcTok3[i+0]
		if c == char {
			c = CalcTok3[i+1]
			goto out
		}
	}

out:
	if c == 0 {
		c = CalcTok2[1] /* unknown char */
	}
	if CalcDebug >= 3 {
		__yyfmt__.Printf("lex %s(%d)\n", CalcTokname(c), uint(char))
	}
	return c
}

func CalcParse(Calclex CalcLexer) int {
	var Calcn int
	var Calclval CalcSymType
	var CalcVAL CalcSymType
	CalcS := make([]CalcSymType, CalcMaxDepth)

	Nerrs := 0   /* number of errors */
	Errflag := 0 /* error recovery flag */
	Calcstate := 0
	Calcchar := -1
	Calcp := -1
	goto Calcstack

ret0:
	return 0

ret1:
	return 1

Calcstack:
	/* put a state and value onto the stack */
	if CalcDebug >= 4 {
		__yyfmt__.Printf("char %v in %v\n", CalcTokname(Calcchar), CalcStatname(Calcstate))
	}

	Calcp++
	if Calcp >= len(CalcS) {
		nyys := make([]CalcSymType, len(CalcS)*2)
		copy(nyys, CalcS)
		CalcS = nyys
	}
	CalcS[Calcp] = CalcVAL
	CalcS[Calcp].yys = Calcstate

Calcnewstate:
	Calcn = CalcPact[Calcstate]
	if Calcn <= CalcFlag {
		goto Calcdefault /* simple state */
	}
	if Calcchar < 0 {
		Calcchar = Calclex1(Calclex, &Calclval)
	}
	Calcn += Calcchar
	if Calcn < 0 || Calcn >= CalcLast {
		goto Calcdefault
	}
	Calcn = CalcAct[Calcn]
	if CalcChk[Calcn] == Calcchar { /* valid shift */
		Calcchar = -1
		CalcVAL = Calclval
		Calcstate = Calcn
		if Errflag > 0 {
			Errflag--
		}
		goto Calcstack
	}

Calcdefault:
	/* default state action */
	Calcn = CalcDef[Calcstate]
	if Calcn == -2 {
		if Calcchar < 0 {
			Calcchar = Calclex1(Calclex, &Calclval)
		}

		/* look through exception table */
		xi := 0
		for {
			if CalcExca[xi+0] == -1 && CalcExca[xi+1] == Calcstate {
				break
			}
			xi += 2
		}
		for xi += 2; ; xi += 2 {
			Calcn = CalcExca[xi+0]
			if Calcn < 0 || Calcn == Calcchar {
				break
			}
		}
		Calcn = CalcExca[xi+1]
		if Calcn < 0 {
			goto ret0
		}
	}
	if Calcn == 0 {
		/* error ... attempt to resume parsing */
		switch Errflag {
		case 0: /* brand new error */
			Calclex.Error("syntax error")
			Nerrs++
			if CalcDebug >= 1 {
				__yyfmt__.Printf("%s", CalcStatname(Calcstate))
				__yyfmt__.Printf(" saw %s\n", CalcTokname(Calcchar))
			}
			fallthrough

		case 1, 2: /* incompletely recovered error ... try again */
			Errflag = 3

			/* find a state where "error" is a legal shift action */
			for Calcp >= 0 {
				Calcn = CalcPact[CalcS[Calcp].yys] + CalcErrCode
				if Calcn >= 0 && Calcn < CalcLast {
					Calcstate = CalcAct[Calcn] /* simulate a shift of "error" */
					if CalcChk[Calcstate] == CalcErrCode {
						goto Calcstack
					}
				}

				/* the current p has no shift on "error", pop stack */
				if CalcDebug >= 2 {
					__yyfmt__.Printf("error recovery pops state %d\n", CalcS[Calcp].yys)
				}
				Calcp--
			}
			/* there is no state on the stack with an error shift ... abort */
			goto ret1

		case 3: /* no shift yet; clobber input char */
			if CalcDebug >= 2 {
				__yyfmt__.Printf("error recovery discards %s\n", CalcTokname(Calcchar))
			}
			if Calcchar == CalcEofCode {
				goto ret1
			}
			Calcchar = -1
			goto Calcnewstate /* try again in the same state */
		}
	}

	/* reduction by production Calcn */
	if CalcDebug >= 2 {
		__yyfmt__.Printf("reduce %v in:\n\t%v\n", Calcn, CalcStatname(Calcstate))
	}

	Calcnt := Calcn
	Calcpt := Calcp
	_ = Calcpt // guard against "declared and not used"

	Calcp -= CalcR2[Calcn]
	CalcVAL = CalcS[Calcp+1]

	/* consult goto table to find next state */
	Calcn = CalcR1[Calcn]
	Calcg := CalcPgo[Calcn]
	Calcj := Calcg + CalcS[Calcp].yys + 1

	if Calcj >= CalcLast {
		Calcstate = CalcAct[Calcg]
	} else {
		Calcstate = CalcAct[Calcj]
		if CalcChk[Calcstate] != -Calcn {
			Calcstate = CalcAct[Calcg]
		}
	}
	// dummy call; replaced with literal code
	switch Calcnt {

	case 1:
		//line calc.y:78
		{
			fmt.Println("file begin")
			CalcVAL.file = ast.FileAst{Decls: []ast.Declaration{CalcS[Calcpt-0].declaration}}
		}
	case 2:
		//line calc.y:83
		{
			fmt.Println("add decl to list")
			CalcS[Calcpt-1].file.Decls = append(CalcS[Calcpt-1].file.Decls, CalcS[Calcpt-0].declaration)
			CalcVAL.file = CalcS[Calcpt-1].file
		}
	case 3:
		//line calc.y:89
		{
			fmt.Println("EOF")
			mainResult = CalcS[Calcpt-1].file
		}
	case 4:
		//line calc.y:95
		{
			fmt.Println("init stmt block")
			blockstmts = append(blockstmts, CalcS[Calcpt-1].statement_list)
			CalcVAL.statement_block = len(blockstmts) - 1
		}
	case 5:
		//line calc.y:103
		{
			fmt.Println("list statement begin")
			fmt.Println(CalcS[Calcpt-0].statement)
			CalcVAL.statement_list = ast.BlockStmt{List: []ast.Statement{CalcS[Calcpt-0].statement}}
		}
	case 6:
		//line calc.y:109
		{
			fmt.Println("add stmt to list")
			CalcS[Calcpt-1].statement_list.List = append(CalcS[Calcpt-1].statement_list.List, CalcS[Calcpt-0].statement)
			CalcVAL.statement_list = CalcS[Calcpt-1].statement_list
		}
	case 7:
		//line calc.y:116
		{
			fmt.Println("decl --> stmt")
			fmt.Println(CalcS[Calcpt-0].declaration)
			CalcVAL.statement = &ast.DeclStmt{Decl: CalcS[Calcpt-0].declaration}
		}
	case 8:
		//line calc.y:122
		{
			fmt.Println("assigned --> stmt")
			CalcVAL.statement = &ast.AssignStmt{
				Ident: CalcS[Calcpt-3].expression,
				Op:    CalcS[Calcpt-2].token.TokenType,
				X:     CalcS[Calcpt-1].expression,
			}

		}
	case 9:
		//line calc.y:132
		{
			fmt.Println("comment")
			CalcVAL.statement = &ast.EmptyStmt{}
		}
	case 10:
		//line calc.y:137
		{
			// conflict
			fmt.Println("return stmt")
			CalcVAL.statement = &ast.ReturnStmt{
				X: CalcS[Calcpt-0].expression,
			}

		}
	case 11:
		//line calc.y:146
		{
			fmt.Println("if stmt with else")
			CalcVAL.statement = &ast.IfStmt{
				Cond: CalcS[Calcpt-3].expression,
				Body: &blockstmts[CalcS[Calcpt-2].statement_block],
				Else: &blockstmts[CalcS[Calcpt-0].statement_block],
			}
		}
	case 12:
		//line calc.y:155
		{
			fmt.Println("if stmt")
			CalcVAL.statement = &ast.IfStmt{
				Cond: CalcS[Calcpt-1].expression,
				Body: &blockstmts[CalcS[Calcpt-0].statement_block],
			}
		}
	case 13:
		//line calc.y:163
		{
			fmt.Println("for stmt")
			CalcVAL.statement = &ast.ForStmt{
				X:    CalcS[Calcpt-1].expression,
				Body: &blockstmts[CalcS[Calcpt-0].statement_block],
			}
		}
	case 14:
		//line calc.y:171
		{
			fmt.Println("stmt + new line")
			CalcVAL.statement = CalcS[Calcpt-1].statement
		}
	case 15:
		//line calc.y:177
		{
			fmt.Println("var")
			CalcVAL.declaration = &ast.VarDecl{
				Name: &identifiers[CalcS[Calcpt-1].identifier],
				Type: CalcS[Calcpt-0].expression,
			}
		}
	case 16:
		//line calc.y:185
		{
			fmt.Println("func")
			CalcVAL.declaration = &ast.FuncDecl{
				Name:    &identifiers[CalcS[Calcpt-4].identifier],
				RetType: CalcS[Calcpt-1].expression,
				Body:    &blockstmts[CalcS[Calcpt-0].statement_block],
			}
		}
	case 17:
		//line calc.y:194
		{
			fmt.Println("func")
			CalcVAL.declaration = &ast.FuncDecl{
				Name:    &identifiers[CalcS[Calcpt-5].identifier],
				Params:  CalcS[Calcpt-3].field_list,
				RetType: CalcS[Calcpt-1].expression,
				Body:    &blockstmts[CalcS[Calcpt-0].statement_block],
			}
		}
	case 18:
		//line calc.y:204
		{
			fmt.Println("decl new line")
			CalcVAL.declaration = CalcS[Calcpt-1].declaration
		}
	case 19:
		//line calc.y:211
		{
			CalcVAL.field_list = []ast.Field{CalcS[Calcpt-0].field}
		}
	case 20:
		//line calc.y:215
		{
			CalcVAL.field_list = append(CalcS[Calcpt-2].field_list, CalcS[Calcpt-0].field)
		}
	case 21:
		//line calc.y:221
		{
			fmt.Println("field")
			CalcVAL.field = ast.Field{
				Name: &identifiers[CalcS[Calcpt-1].identifier],
				Type: CalcS[Calcpt-0].expression,
			}
		}
	case 22:
		//line calc.y:231
		{
			CalcVAL.expression_list = []ast.Expression{CalcS[Calcpt-0].expression}
		}
	case 23:
		//line calc.y:235
		{
			CalcVAL.expression_list = append(CalcS[Calcpt-2].expression_list, CalcS[Calcpt-0].expression)
		}
	case 24:
		//line calc.y:241
		{
			fmt.Printf("expr <- LPAREN expr RPAREN\n")
			CalcVAL.expression = CalcS[Calcpt-1].expression
		}
	case 25:
		//line calc.y:246
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   &identifiers[CalcS[Calcpt-3].identifier],
				OpT: CalcS[Calcpt-2].token,
				Y:   CalcS[Calcpt-1].expression,
			}
		}
	case 26:
		//line calc.y:254
		{
			// conflict
			CalcVAL.expression = &ast.CallExpr{
				Fun:  &identifiers[CalcS[Calcpt-3].identifier],
				Args: CalcS[Calcpt-1].expression_list,
			}
		}
	case 27:
		//line calc.y:262
		{
			CalcVAL.expression = &ast.CallExpr{
				Fun: &identifiers[CalcS[Calcpt-2].identifier],
			}
		}
	case 28:
		//line calc.y:268
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 29:
		//line calc.y:277
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 30:
		//line calc.y:286
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 31:
		//line calc.y:295
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 32:
		//line calc.y:304
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 33:
		//line calc.y:313
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 34:
		//line calc.y:321
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 35:
		//line calc.y:329
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 36:
		//line calc.y:337
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-0].expression,
				OpT: CalcS[Calcpt-1].token,
			}
		}
	case 37:
		//line calc.y:345
		{
			fmt.Println("identifier -> expr")
			CalcVAL.expression = &identifiers[CalcS[Calcpt-0].identifier]
		}
	case 38:
		//line calc.y:350
		{
			fmt.Println("expr <- number")
			CalcVAL.expression = CalcS[Calcpt-0].expression
		}
	case 39:
		//line calc.y:357
		{
			fmt.Println("identifier")
			ident := ast.Ident{
				Name: CalcS[Calcpt-0].token.Value,
				T:    CalcS[Calcpt-0].token,
			}
			identifiers = append(identifiers, ident)
			CalcVAL.identifier = len(identifiers) - 1
		}
	case 40:
		//line calc.y:369
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 41:
		//line calc.y:374
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 42:
		//line calc.y:379
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 43:
		//line calc.y:384
		{
			fmt.Println("array")
			CalcVAL.expression = &ast.ArrayType{
				Index: -1,
				At:    CalcS[Calcpt-0].expression,
			}
		}
	case 44:
		//line calc.y:392
		{
			value, err := strconv.Atoi(CalcS[Calcpt-2].token.Value)
			if err != nil {
				panic(err)
			}
			fmt.Println("array")
			CalcVAL.expression = &ast.ArrayType{
				Index: value,
				At:    CalcS[Calcpt-0].expression,
			}
		}
	case 45:
		//line calc.y:406
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 46:
		//line calc.y:411
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 47:
		//line calc.y:418
		{
			CalcVAL.token = CalcS[Calcpt-0].token
		}
	}
	goto Calcstack /* stack new state and value */
}
