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
const STRING_VALUE = 57360
const INT = 57361
const FLOAT = 57362
const STRING = 57363
const NEW_LINE = 57364
const VAR = 57365
const ASSIGNED = 57366
const IDENTIFIER = 57367
const ADD = 57368
const SUB = 57369
const MUL = 57370
const QUO = 57371
const REM = 57372
const SIN = 57373
const COS = 57374
const SQRT = 57375
const LPAREN = 57376
const RPAREN = 57377
const EQUAL = 57378
const NOT_EQUAL = 57379
const GREATE = 57380
const AND = 57381
const OR = 57382
const UMINUS = 57383

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
	"STRING_VALUE",
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
	"EQUAL",
	"NOT_EQUAL",
	"GREATE",
	"AND",
	"OR",
	"UMINUS",
}
var CalcStatenames = []string{}

const CalcEofCode = 1
const CalcErrCode = 2
const CalcMaxDepth = 200

//line calc.y:474

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
		llvmBuilder := new(ast.LlvmBuilderVisitor)
		mainResult.Accept(llvmBuilder)
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

const CalcNprod = 54
const CalcPrivate = 57344

var CalcTokenNames []string
var CalcStates []string

const CalcLast = 271

var CalcAct = []int{

	40, 31, 59, 60, 61, 62, 68, 77, 76, 38,
	9, 107, 63, 64, 65, 66, 67, 59, 60, 61,
	62, 68, 75, 19, 53, 54, 106, 63, 64, 65,
	66, 67, 9, 103, 50, 36, 28, 16, 47, 48,
	49, 45, 95, 69, 70, 71, 72, 56, 9, 73,
	57, 78, 7, 104, 35, 17, 27, 19, 20, 79,
	80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	74, 101, 90, 91, 93, 96, 97, 98, 99, 59,
	60, 61, 62, 68, 102, 61, 62, 68, 105, 63,
	64, 65, 66, 67, 22, 6, 59, 60, 61, 62,
	68, 4, 4, 108, 109, 52, 63, 64, 65, 66,
	67, 100, 25, 3, 3, 59, 60, 61, 62, 68,
	32, 18, 21, 34, 32, 63, 64, 65, 66, 67,
	59, 60, 61, 62, 68, 39, 2, 5, 37, 92,
	63, 64, 65, 66, 67, 59, 60, 61, 62, 68,
	59, 60, 61, 62, 68, 63, 64, 65, 66, 67,
	58, 1, 59, 60, 61, 62, 68, 59, 60, 61,
	62, 68, 63, 64, 65, 66, 67, 63, 64, 65,
	66, 67, 55, 43, 94, 44, 42, 4, 41, 51,
	15, 0, 19, 53, 54, 0, 12, 13, 14, 3,
	0, 9, 0, 50, 0, 0, 0, 47, 48, 49,
	45, 43, 0, 44, 42, 4, 41, 0, 0, 0,
	19, 53, 54, 0, 0, 0, 0, 3, 0, 9,
	0, 50, 19, 53, 54, 47, 48, 49, 45, 0,
	46, 9, 11, 50, 8, 10, 0, 47, 48, 49,
	45, 0, 0, 0, 0, 0, 0, 23, 0, 0,
	24, 0, 0, 26, 0, 0, 29, 0, 30, 23,
	33,
}
var CalcPact = []int{

	90, 91, 30, -15, -15, 30, -1000, -1000, 177, -1000,
	3, -1000, -1000, -1000, -1000, 41, 23, 177, 98, -1000,
	177, 21, -1000, 177, -1000, 177, 115, 177, -15, -1000,
	-1000, -1000, 32, 115, -1000, 204, -1000, 176, 28, 30,
	136, -1000, 216, 216, 216, 216, 36, -12, -26, -27,
	216, -1000, -1000, -1000, -1000, -1000, 28, -1000, 216, 216,
	216, 216, 216, 216, 216, 216, 216, 216, 216, 141,
	119, 119, 104, 216, 7, 216, 216, 216, -1000, 89,
	57, 57, -1000, -1000, 124, 124, 124, 124, 124, -1000,
	63, -1000, -1000, 70, 18, -1000, 141, 53, -9, -24,
	-1000, 115, -1000, 216, -1000, -1000, -1000, -1000, -1000, 141,
}
var CalcPgo = []int{

	0, 105, 0, 189, 242, 184, 135, 240, 161, 9,
	138, 1, 94, 122,
}
var CalcR1 = []int{

	0, 8, 8, 8, 11, 10, 10, 9, 9, 9,
	9, 9, 9, 9, 9, 6, 6, 6, 6, 13,
	13, 12, 5, 5, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 7, 4, 4, 4, 4, 4,
	3, 3, 3, 1,
}
var CalcR2 = []int{

	0, 1, 2, 2, 4, 1, 2, 1, 4, 1,
	2, 5, 3, 3, 2, 3, 6, 7, 2, 1,
	3, 2, 1, 3, 3, 4, 4, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 4, 4,
	4, 2, 1, 1, 1, 1, 1, 1, 3, 4,
	1, 1, 1, 1,
}
var CalcChk = []int{

	-1000, -8, -6, 23, 11, -6, 4, 22, -7, 25,
	-7, -4, 19, 20, 21, 13, 34, 14, -1, 16,
	35, -13, -12, -7, -4, 14, -4, 35, 15, -4,
	-4, -11, 5, -4, -12, 22, -11, -10, -9, -6,
	-2, 12, 10, 7, 9, 34, -7, 31, 32, 33,
	27, -3, -1, 17, 18, 6, -9, 22, 24, 26,
	27, 28, 29, 36, 37, 38, 39, 40, 30, -2,
	-2, -2, -2, 13, 34, 34, 34, 34, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-11, -11, 35, -2, -5, 35, -2, -2, -2, -2,
	22, 8, 14, 15, 35, 35, 35, 35, -11, -2,
}
var CalcDef = []int{

	0, -2, 1, 0, 0, 2, 3, 18, 0, 44,
	0, 15, 45, 46, 47, 0, 0, 0, 0, 53,
	0, 0, 19, 0, 48, 0, 0, 0, 0, 21,
	49, 16, 0, 0, 20, 0, 17, 0, 5, 7,
	0, 9, 0, 0, 0, 0, 42, 0, 0, 0,
	0, 43, 50, 51, 52, 4, 6, 14, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 10,
	0, 0, 0, 0, 0, 0, 0, 0, 41, 0,
	28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
	12, 13, 24, 0, 0, 27, 22, 0, 0, 0,
	8, 0, 25, 0, 26, 38, 39, 40, 11, 23,
}
var CalcTok1 = []int{

	1,
}
var CalcTok2 = []int{

	2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
	12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
	22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
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
		//line calc.y:79
		{
			fmt.Println("file begin")
			CalcVAL.file = ast.FileAst{Decls: []ast.Declaration{CalcS[Calcpt-0].declaration}}
		}
	case 2:
		//line calc.y:84
		{
			fmt.Println("add decl to list")
			CalcS[Calcpt-1].file.Decls = append(CalcS[Calcpt-1].file.Decls, CalcS[Calcpt-0].declaration)
			CalcVAL.file = CalcS[Calcpt-1].file
		}
	case 3:
		//line calc.y:90
		{
			fmt.Println("EOF")
			mainResult = CalcS[Calcpt-1].file
		}
	case 4:
		//line calc.y:96
		{
			fmt.Println("init stmt block")
			blockstmts = append(blockstmts, CalcS[Calcpt-1].statement_list)
			CalcVAL.statement_block = len(blockstmts) - 1
		}
	case 5:
		//line calc.y:104
		{
			fmt.Println("list statement begin")
			fmt.Println(CalcS[Calcpt-0].statement)
			CalcVAL.statement_list = ast.BlockStmt{List: []ast.Statement{CalcS[Calcpt-0].statement}}
		}
	case 6:
		//line calc.y:110
		{
			fmt.Println("add stmt to list")
			CalcS[Calcpt-1].statement_list.List = append(CalcS[Calcpt-1].statement_list.List, CalcS[Calcpt-0].statement)
			CalcVAL.statement_list = CalcS[Calcpt-1].statement_list
		}
	case 7:
		//line calc.y:117
		{
			fmt.Println("decl --> stmt")
			fmt.Println(CalcS[Calcpt-0].declaration)
			CalcVAL.statement = &ast.DeclStmt{Decl: CalcS[Calcpt-0].declaration}
		}
	case 8:
		//line calc.y:123
		{
			fmt.Println("assigned --> stmt")
			CalcVAL.statement = &ast.AssignStmt{
				Ident: CalcS[Calcpt-3].expression,
				Op:    CalcS[Calcpt-2].token.TokenType,
				X:     CalcS[Calcpt-1].expression,
			}

		}
	case 9:
		//line calc.y:133
		{
			fmt.Println("comment")
			CalcVAL.statement = &ast.EmptyStmt{}
		}
	case 10:
		//line calc.y:138
		{
			// conflict
			fmt.Println("return stmt")
			CalcVAL.statement = &ast.ReturnStmt{
				X: CalcS[Calcpt-0].expression,
			}

		}
	case 11:
		//line calc.y:147
		{
			fmt.Println("if stmt with else")
			CalcVAL.statement = &ast.IfStmt{
				Cond: CalcS[Calcpt-3].expression,
				Body: &blockstmts[CalcS[Calcpt-2].statement_block],
				Else: &blockstmts[CalcS[Calcpt-0].statement_block],
			}
		}
	case 12:
		//line calc.y:156
		{
			fmt.Println("if stmt")
			CalcVAL.statement = &ast.IfStmt{
				Cond: CalcS[Calcpt-1].expression,
				Body: &blockstmts[CalcS[Calcpt-0].statement_block],
			}
		}
	case 13:
		//line calc.y:164
		{
			fmt.Println("for stmt")
			CalcVAL.statement = &ast.ForStmt{
				X:    CalcS[Calcpt-1].expression,
				Body: &blockstmts[CalcS[Calcpt-0].statement_block],
			}
		}
	case 14:
		//line calc.y:172
		{
			fmt.Println("stmt + new line")
			CalcVAL.statement = CalcS[Calcpt-1].statement
		}
	case 15:
		//line calc.y:178
		{
			fmt.Println("var")
			CalcVAL.declaration = &ast.VarDecl{
				Name: &identifiers[CalcS[Calcpt-1].identifier],
				Type: CalcS[Calcpt-0].expression,
			}
		}
	case 16:
		//line calc.y:186
		{
			fmt.Println("func")
			CalcVAL.declaration = &ast.FuncDecl{
				Name:    &identifiers[CalcS[Calcpt-4].identifier],
				RetType: CalcS[Calcpt-1].expression,
				Body:    &blockstmts[CalcS[Calcpt-0].statement_block],
			}
		}
	case 17:
		//line calc.y:195
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
		//line calc.y:205
		{
			fmt.Println("decl new line")
			CalcVAL.declaration = CalcS[Calcpt-1].declaration
		}
	case 19:
		//line calc.y:212
		{
			CalcVAL.field_list = []ast.Field{CalcS[Calcpt-0].field}
		}
	case 20:
		//line calc.y:216
		{
			CalcVAL.field_list = append(CalcS[Calcpt-2].field_list, CalcS[Calcpt-0].field)
		}
	case 21:
		//line calc.y:222
		{
			fmt.Println("field")
			CalcVAL.field = ast.Field{
				Name: &identifiers[CalcS[Calcpt-1].identifier],
				Type: CalcS[Calcpt-0].expression,
			}
		}
	case 22:
		//line calc.y:232
		{
			CalcVAL.expression_list = []ast.Expression{CalcS[Calcpt-0].expression}
		}
	case 23:
		//line calc.y:236
		{
			CalcVAL.expression_list = append(CalcS[Calcpt-2].expression_list, CalcS[Calcpt-0].expression)
		}
	case 24:
		//line calc.y:242
		{
			fmt.Printf("expr <- LPAREN expr RPAREN\n")
			CalcVAL.expression = CalcS[Calcpt-1].expression
		}
	case 25:
		//line calc.y:247
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   &identifiers[CalcS[Calcpt-3].identifier],
				OpT: CalcS[Calcpt-2].token,
				Y:   CalcS[Calcpt-1].expression,
			}
		}
	case 26:
		//line calc.y:255
		{
			// conflict
			CalcVAL.expression = &ast.CallExpr{
				Fun:  &identifiers[CalcS[Calcpt-3].identifier],
				Args: CalcS[Calcpt-1].expression_list,
			}
		}
	case 27:
		//line calc.y:263
		{
			CalcVAL.expression = &ast.CallExpr{
				Fun: &identifiers[CalcS[Calcpt-2].identifier],
			}
		}
	case 28:
		//line calc.y:269
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 29:
		//line calc.y:278
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 30:
		//line calc.y:287
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 31:
		//line calc.y:296
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 32:
		//line calc.y:305
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 33:
		//line calc.y:314
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 34:
		//line calc.y:323
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 35:
		//line calc.y:332
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 36:
		//line calc.y:341
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 37:
		//line calc.y:350
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 38:
		//line calc.y:359
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 39:
		//line calc.y:367
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 40:
		//line calc.y:375
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 41:
		//line calc.y:383
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-0].expression,
				OpT: CalcS[Calcpt-1].token,
			}
		}
	case 42:
		//line calc.y:391
		{
			fmt.Println("identifier -> expr")
			CalcVAL.expression = &identifiers[CalcS[Calcpt-0].identifier]
		}
	case 43:
		//line calc.y:396
		{
			fmt.Println("expr <- number")
			CalcVAL.expression = CalcS[Calcpt-0].expression
		}
	case 44:
		//line calc.y:403
		{
			fmt.Println("identifier")
			ident := ast.Ident{
				Name: CalcS[Calcpt-0].token.Value,
				T:    CalcS[Calcpt-0].token,
			}
			identifiers = append(identifiers, ident)
			CalcVAL.identifier = len(identifiers) - 1
		}
	case 45:
		//line calc.y:415
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 46:
		//line calc.y:420
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 47:
		//line calc.y:425
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 48:
		//line calc.y:430
		{
			fmt.Println("array")
			CalcVAL.expression = &ast.ArrayType{
				Index: -1,
				At:    CalcS[Calcpt-0].expression,
			}
		}
	case 49:
		//line calc.y:438
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
	case 50:
		//line calc.y:452
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 51:
		//line calc.y:457
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 52:
		//line calc.y:462
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 53:
		//line calc.y:469
		{
			CalcVAL.token = CalcS[Calcpt-0].token
		}
	}
	goto Calcstack /* stack new state and value */
}
