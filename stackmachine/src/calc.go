//line calc.y:7

package main

import __yyfmt__ "fmt"

//line calc.y:10
import (
	"ast"
	"bufio"
	"bytes"
	"fmt"
	"lexer"
	"os"
	"stackmachine"
	"token"
)

var regs = make(map[string]ast.Expression)
var base ast.Expression

var mainResult ast.Expression
var stackMachineExpr string

//line calc.y:32
type CalcSymType struct {
	yys     int
	val     int
	nodeAst ast.Expression
	token   token.Token
	lex     CalcLex
}

const EOF = 57346
const INT_NUMBER = 57347
const FLOAT_NUMBER = 57348
const ADD = 57349
const SUB = 57350
const MUL = 57351
const QUO = 57352
const REM = 57353
const SIN = 57354
const COS = 57355
const SQRT = 57356
const LPAREN = 57357
const RPAREN = 57358
const ASSIGNED = 57359
const IDENTIFIER = 57360
const UMINUS = 57361

var CalcToknames = []string{
	"EOF",
	"INT_NUMBER",
	"FLOAT_NUMBER",
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
	"ASSIGNED",
	"IDENTIFIER",
	"UMINUS",
}
var CalcStatenames = []string{}

const CalcEofCode = 1
const CalcErrCode = 2
const CalcMaxDepth = 200

//line calc.y:189

/*  start  of  programs  */

type CalcLex struct {
	tokens   []token.Token
	tokenMap map[int]int
	nodeAst  ast.Expression
	pos      int
}

func (l *CalcLex) Lex(lval *CalcSymType) int {
	if l.pos == len(l.tokens) {
		return 0
	}
	var c token.Token = l.tokens[l.pos]
	l.pos += 1

	if lval.token.TokenType == token.EOF {
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
		stackMachineExpr = ""

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
		stackmachineObj.Execute(fi)
		stackmachineObj.PrintStackAll()
	}
}

func readline(fi *bufio.Reader) (string, bool) {
	s, err := fi.ReadString('\n')
	if err != nil {
		fmt.Println(err)
		return "", false
	}
	return s, true
}

//line yacctab:1
var CalcExca = []int{
	-1, 1,
	1, -1,
	-2, 0,
}

const CalcNprod = 20
const CalcPrivate = 57344

var CalcTokenNames []string
var CalcStates []string

const CalcLast = 101

var CalcAct = []int{

	3, 19, 24, 23, 22, 1, 20, 16, 17, 18,
	25, 2, 10, 0, 0, 26, 27, 28, 29, 30,
	31, 0, 0, 33, 34, 35, 11, 12, 0, 9,
	0, 0, 0, 6, 7, 8, 5, 11, 12, 21,
	9, 0, 0, 0, 6, 7, 8, 5, 0, 0,
	4, 14, 15, 16, 17, 18, 0, 0, 0, 0,
	38, 14, 15, 16, 17, 18, 0, 0, 0, 0,
	37, 14, 15, 16, 17, 18, 0, 0, 0, 0,
	36, 14, 15, 16, 17, 18, 0, 0, 13, 0,
	32, 14, 15, 16, 17, 18, 14, 15, 16, 17,
	18,
}
var CalcPact = []int{

	32, -1000, -1000, 84, -16, 21, -11, -12, -13, 21,
	-1000, -1000, -1000, -1000, 21, 21, 21, 21, 21, 21,
	74, -1000, 21, 21, 21, -1000, -2, -2, -1000, -1000,
	-1000, 89, -1000, 64, 54, 44, -1000, -1000, -1000,
}
var CalcPgo = []int{

	0, 0, 12, 11, 5,
}
var CalcR1 = []int{

	0, 4, 4, 3, 3, 3, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
}
var CalcR2 = []int{

	0, 0, 1, 1, 3, 2, 3, 3, 3, 3,
	3, 3, 4, 4, 4, 2, 1, 1, 1, 1,
}
var CalcChk = []int{

	-1000, -4, -3, -1, 18, 15, 12, 13, 14, 8,
	-2, 5, 6, 4, 7, 8, 9, 10, 11, 17,
	-1, 18, 15, 15, 15, -1, -1, -1, -1, -1,
	-1, -1, 16, -1, -1, -1, 16, 16, 16,
}
var CalcDef = []int{

	1, -2, 2, 3, 16, 0, 0, 0, 0, 0,
	17, 18, 19, 5, 0, 0, 0, 0, 0, 0,
	0, 16, 0, 0, 0, 15, 7, 8, 9, 10,
	11, 4, 6, 0, 0, 0, 12, 13, 14,
}
var CalcTok1 = []int{

	1,
}
var CalcTok2 = []int{

	2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
	12, 13, 14, 15, 16, 17, 18, 19,
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

	case 3:
		//line calc.y:63
		{
			fmt.Println("end expr")
			CalcVAL.nodeAst = CalcS[Calcpt-0].nodeAst
		}
	case 4:
		//line calc.y:68
		{
			regs[CalcS[Calcpt-2].token.Value] = CalcS[Calcpt-0].nodeAst
		}
	case 5:
		//line calc.y:72
		{
			fmt.Println("EOF")
			mainResult = CalcS[Calcpt-1].nodeAst
		}
	case 6:
		//line calc.y:80
		{
			fmt.Printf("expr <- LPAREN expr RPAREN\n")
			CalcVAL.nodeAst = CalcS[Calcpt-1].nodeAst
		}
	case 7:
		//line calc.y:85
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.nodeAst = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].nodeAst,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].nodeAst,
			}
			stackMachineExpr += "add\n"
		}
	case 8:
		//line calc.y:95
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.nodeAst = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].nodeAst,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].nodeAst,
			}
			stackMachineExpr += "sub\n"
		}
	case 9:
		//line calc.y:105
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.nodeAst = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].nodeAst,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].nodeAst,
			}
			stackMachineExpr += "mul\n"
		}
	case 10:
		//line calc.y:115
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.nodeAst = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].nodeAst,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].nodeAst,
			}
		}
	case 11:
		//line calc.y:124
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.nodeAst = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].nodeAst,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].nodeAst,
			}
		}
	case 12:
		//line calc.y:133
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.nodeAst = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].nodeAst,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 13:
		//line calc.y:141
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.nodeAst = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].nodeAst,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 14:
		//line calc.y:149
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.nodeAst = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].nodeAst,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 15:
		//line calc.y:157
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.nodeAst = &ast.UnaryExpr{
				X:   CalcS[Calcpt-0].nodeAst,
				OpT: CalcS[Calcpt-1].token,
			}
			stackMachineExpr += "div\n"
		}
	case 16:
		//line calc.y:166
		{
			CalcVAL.nodeAst = regs[CalcS[Calcpt-0].token.Value]
		}
	case 17:
		//line calc.y:170
		{
			fmt.Printf("expr <- number\n")
			CalcVAL.nodeAst = CalcS[Calcpt-0].nodeAst
		}
	case 18:
		//line calc.y:177
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.nodeAst = &ast.BasicLit{T: CalcS[Calcpt-0].token}
			stackMachineExpr += "push " + CalcS[Calcpt-0].token.Value + "\n "
		}
	case 19:
		//line calc.y:183
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.nodeAst = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	}
	goto Calcstack /* stack new state and value */
}
