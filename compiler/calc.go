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
	"token"
)

var regs = make(map[string]ast.Expression)
var base ast.Expression

var mainResult ast.BlockStmt

//line calc.y:31
type CalcSymType struct {
	yys             int
	val             int
	expression      ast.Expression
	declaration     ast.Declaration
	statement       ast.Statement
	statement_block ast.BlockStmt
	identifier      ast.Ident
	token           token.Token
}

const EOF = 57346
const LBRACE = 57347
const RBRACE = 57348
const INT_NUMBER = 57349
const FLOAT_NUMBER = 57350
const INT = 57351
const FLOAT = 57352
const STRING = 57353
const NEW_LINE = 57354
const VAR = 57355
const ASSIGNED = 57356
const IDENTIFIER = 57357
const ADD = 57358
const SUB = 57359
const MUL = 57360
const QUO = 57361
const REM = 57362
const SIN = 57363
const COS = 57364
const SQRT = 57365
const LPAREN = 57366
const RPAREN = 57367
const UMINUS = 57368

var CalcToknames = []string{
	"EOF",
	"LBRACE",
	"RBRACE",
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

//line calc.y:243

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

const CalcNprod = 24
const CalcPrivate = 57344

var CalcTokenNames []string
var CalcStates []string

const CalcLast = 77

var CalcAct = []int{

	17, 28, 29, 30, 31, 32, 36, 35, 34, 11,
	49, 28, 29, 30, 31, 32, 30, 31, 32, 33,
	48, 15, 10, 37, 11, 14, 5, 26, 2, 38,
	39, 40, 41, 42, 1, 44, 45, 46, 28, 29,
	30, 31, 32, 24, 25, 12, 6, 47, 4, 8,
	23, 0, 10, 22, 11, 9, 3, 19, 20, 21,
	18, 28, 29, 30, 31, 32, 16, 27, 0, 7,
	43, 28, 29, 30, 31, 32, 13,
}
var CalcPact = []int{

	23, 44, 14, -1000, -1000, 9, 39, 13, -1000, 7,
	-6, -1000, -1000, 13, -1000, 36, 18, 55, 36, -16,
	-17, -18, 36, -1000, -1000, -1000, -1000, -1000, 36, 36,
	36, 36, 36, 45, 36, 36, 36, -1000, -2, -2,
	-1000, -1000, -1000, -1000, 22, -5, -15, -1000, -1000, -1000,
}
var CalcPgo = []int{

	0, 0, 50, 55, 49, 69, 46, 34,
}
var CalcR1 = []int{

	0, 7, 7, 7, 6, 6, 5, 5, 5, 4,
	3, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 2, 2,
}
var CalcR2 = []int{

	0, 4, 2, 2, 1, 2, 1, 4, 2, 3,
	1, 3, 3, 3, 3, 3, 3, 4, 4, 4,
	2, 1, 1, 1,
}
var CalcChk = []int{

	-1000, -7, 5, 12, 4, 12, -6, -5, -4, -3,
	13, 15, 6, -5, 12, 14, -3, -1, 24, 21,
	22, 23, 17, -2, 7, 8, 9, 12, 16, 17,
	18, 19, 20, -1, 24, 24, 24, -1, -1, -1,
	-1, -1, -1, 25, -1, -1, -1, 25, 25, 25,
}
var CalcDef = []int{

	0, -2, 0, 2, 3, 0, 0, 4, 6, 0,
	0, 10, 1, 5, 8, 0, 0, 0, 0, 0,
	0, 0, 0, 21, 22, 23, 9, 7, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 20, 12, 13,
	14, 15, 16, 11, 0, 0, 0, 17, 18, 19,
}
var CalcTok1 = []int{

	1,
}
var CalcTok2 = []int{

	2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
	12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
	22, 23, 24, 25, 26,
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
		//line calc.y:63
		{
			fmt.Println("init stmt block")
			CalcVAL.statement_block = CalcS[Calcpt-1].statement_block
		}
	case 2:
		//line calc.y:68
		{
			CalcVAL.statement_block = CalcS[Calcpt-1].statement_block
		}
	case 3:
		//line calc.y:72
		{
			fmt.Println("EOF")
			mainResult = CalcS[Calcpt-1].statement_block
		}
	case 4:
		//line calc.y:79
		{
			fmt.Println("list statement begin")
			fmt.Println(CalcS[Calcpt-0].statement)
			CalcVAL.statement_block = ast.BlockStmt{List: []ast.Statement{CalcS[Calcpt-0].statement}}
		}
	case 5:
		//line calc.y:85
		{
			fmt.Println("add stmt to list")
			CalcS[Calcpt-1].statement_block.List = append(CalcS[Calcpt-1].statement_block.List, CalcS[Calcpt-0].statement)
			CalcVAL.statement_block = CalcS[Calcpt-1].statement_block
		}
	case 6:
		//line calc.y:101
		{
			fmt.Println("decl --> stmt")
			fmt.Println(CalcS[Calcpt-0].declaration)
			CalcVAL.statement = &ast.DeclStmt{Decl: CalcS[Calcpt-0].declaration}
		}
	case 7:
		//line calc.y:107
		{
			fmt.Println("assigned --> stmt")
			CalcVAL.statement = &ast.AssignStmt{
				Name: &CalcS[Calcpt-3].identifier,
				Op:   CalcS[Calcpt-2].token.TokenType,
				X:    CalcS[Calcpt-1].expression,
			}

		}
	case 8:
		//line calc.y:117
		{
			fmt.Println("stmt new line")
			CalcVAL.statement = CalcS[Calcpt-1].statement
		}
	case 9:
		//line calc.y:124
		{
			CalcVAL.declaration = &ast.VarDecl{
				Name: &CalcS[Calcpt-1].identifier,
				Type: &ast.BasicLit{T: CalcS[Calcpt-0].token},
			}
		}
	case 10:
		//line calc.y:133
		{
			fmt.Println("identifier")
			CalcVAL.identifier = ast.Ident{
				Name: CalcS[Calcpt-0].token.Value,
				T:    CalcS[Calcpt-0].token,
			}
		}
	case 11:
		//line calc.y:143
		{
			fmt.Printf("expr <- LPAREN expr RPAREN\n")
			CalcVAL.expression = CalcS[Calcpt-1].expression
		}
	case 12:
		//line calc.y:148
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 13:
		//line calc.y:157
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 14:
		//line calc.y:166
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 15:
		//line calc.y:175
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 16:
		//line calc.y:184
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 17:
		//line calc.y:193
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 18:
		//line calc.y:201
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 19:
		//line calc.y:209
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 20:
		//line calc.y:217
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-0].expression,
				OpT: CalcS[Calcpt-1].token,
			}
		}
	case 21:
		//line calc.y:225
		{
			fmt.Printf("expr <- number\n")
			CalcVAL.expression = CalcS[Calcpt-0].expression
		}
	case 22:
		//line calc.y:232
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 23:
		//line calc.y:237
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	}
	goto Calcstack /* stack new state and value */
}
