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

//line calc.y:32
type CalcSymType struct {
	yys             int
	val             int
	expression      ast.Expression
	declaration     ast.Declaration
	statement       ast.Statement
	statement_block ast.BlockStmt
	token           token.Token
	file            ast.FileAst
	field           ast.Field
	field_list      []ast.Field
	identifier      ast.Ident
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

//line calc.y:392

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
	-1, 51,
	13, 35,
	-2, 33,
}

const CalcNprod = 44
const CalcPrivate = 57344

var CalcTokenNames []string
var CalcStates []string

const CalcLast = 185

var CalcAct = []int{

	31, 40, 55, 43, 38, 44, 42, 4, 41, 9,
	71, 70, 19, 54, 69, 16, 28, 9, 3, 20,
	51, 4, 50, 19, 54, 57, 47, 48, 49, 45,
	22, 51, 3, 50, 36, 27, 7, 47, 48, 49,
	45, 35, 56, 88, 64, 65, 66, 67, 61, 62,
	63, 17, 72, 19, 59, 60, 61, 62, 63, 34,
	73, 74, 75, 76, 77, 78, 79, 80, 6, 53,
	82, 83, 84, 85, 43, 4, 44, 42, 4, 41,
	25, 68, 87, 19, 54, 18, 3, 32, 92, 3,
	46, 51, 21, 50, 8, 10, 37, 47, 48, 49,
	45, 59, 60, 61, 62, 63, 1, 23, 52, 0,
	91, 59, 60, 61, 62, 63, 39, 2, 5, 23,
	90, 59, 60, 61, 62, 63, 32, 0, 0, 0,
	89, 59, 60, 61, 62, 63, 0, 86, 0, 0,
	81, 59, 60, 61, 62, 63, 59, 60, 61, 62,
	63, 58, 11, 59, 60, 61, 62, 63, 59, 60,
	61, 62, 63, 0, 0, 0, 0, 0, 0, 0,
	24, 0, 0, 26, 0, 0, 29, 15, 30, 0,
	33, 0, 12, 13, 14,
}
var CalcPact = []int{

	10, 64, 15, -7, -7, 15, -1000, -1000, 164, -1000,
	-18, -1000, -1000, -1000, -1000, 37, -15, 164, 66, -1000,
	164, 1, -1000, 164, -1000, 164, 82, 164, -7, -1000,
	-1000, -1000, 20, 82, -1000, 67, -1000, -4, 4, 15,
	128, -1000, 7, 7, 7, 7, 68, -19, -22, -23,
	7, -1000, -1000, -1000, -1000, -1000, 4, -1000, 7, 7,
	7, 7, 7, 7, 133, 121, 121, 106, 7, 7,
	7, 7, -1000, 116, 21, 21, -1000, -1000, -1000, 74,
	-1000, -1000, 29, 96, 86, 76, -1000, 82, -1000, -1000,
	-1000, -1000, -1000,
}
var CalcPgo = []int{

	0, 69, 1, 108, 152, 116, 90, 106, 4, 96,
	0, 30, 92,
}
var CalcR1 = []int{

	0, 7, 7, 7, 10, 9, 9, 8, 8, 8,
	8, 8, 8, 8, 8, 5, 5, 5, 5, 12,
	12, 11, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 6, 4, 4, 4, 4,
	4, 3, 3, 1,
}
var CalcR2 = []int{

	0, 1, 2, 2, 4, 1, 2, 1, 4, 1,
	2, 5, 3, 3, 2, 3, 6, 7, 2, 1,
	3, 2, 3, 4, 3, 3, 3, 3, 3, 4,
	4, 4, 2, 1, 1, 1, 1, 1, 1, 3,
	4, 1, 1, 1,
}
var CalcChk = []int{

	-1000, -7, -5, 22, 11, -5, 4, 21, -6, 24,
	-6, -4, 18, 19, 20, 13, 33, 14, -1, 16,
	34, -12, -11, -6, -4, 14, -4, 34, 15, -4,
	-4, -10, 5, -4, -11, 21, -10, -9, -8, -5,
	-2, 12, 10, 7, 9, 33, -6, 30, 31, 32,
	26, 24, -3, -1, 17, 6, -8, 21, 23, 25,
	26, 27, 28, 29, -2, -2, -2, -2, 13, 33,
	33, 33, -2, -2, -2, -2, -2, -2, -2, -10,
	-10, 34, -2, -2, -2, -2, 21, 8, 14, 34,
	34, 34, -10,
}
var CalcDef = []int{

	0, -2, 1, 0, 0, 2, 3, 18, 0, 35,
	0, 15, 36, 37, 38, 0, 0, 0, 0, 43,
	0, 0, 19, 0, 39, 0, 0, 0, 0, 21,
	40, 16, 0, 0, 20, 0, 17, 0, 5, 7,
	0, 9, 0, 0, 0, 0, 0, 0, 0, 0,
	0, -2, 34, 41, 42, 4, 6, 14, 0, 0,
	0, 0, 0, 0, 10, 0, 0, 0, 0, 0,
	0, 0, 32, 0, 24, 25, 26, 27, 28, 12,
	13, 22, 0, 0, 0, 0, 8, 0, 23, 29,
	30, 31, 11,
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
		//line calc.y:71
		{
			fmt.Println("file begin")
			CalcVAL.file = ast.FileAst{Decls: []ast.Declaration{CalcS[Calcpt-0].declaration}}
		}
	case 2:
		//line calc.y:76
		{
			fmt.Println("add decl to list")
			CalcS[Calcpt-1].file.Decls = append(CalcS[Calcpt-1].file.Decls, CalcS[Calcpt-0].declaration)
			CalcVAL.file = CalcS[Calcpt-1].file
		}
	case 3:
		//line calc.y:82
		{
			fmt.Println("EOF")
			mainResult = CalcS[Calcpt-1].file
		}
	case 4:
		//line calc.y:88
		{
			fmt.Println("init stmt block")
			CalcVAL.statement_block = CalcS[Calcpt-1].statement_block
		}
	case 5:
		//line calc.y:95
		{
			fmt.Println("list statement begin")
			fmt.Println(CalcS[Calcpt-0].statement)
			CalcVAL.statement_block = ast.BlockStmt{List: []ast.Statement{CalcS[Calcpt-0].statement}}
		}
	case 6:
		//line calc.y:101
		{
			fmt.Println("add stmt to list")
			CalcS[Calcpt-1].statement_block.List = append(CalcS[Calcpt-1].statement_block.List, CalcS[Calcpt-0].statement)
			CalcVAL.statement_block = CalcS[Calcpt-1].statement_block
		}
	case 7:
		//line calc.y:108
		{
			fmt.Println("decl --> stmt")
			fmt.Println(CalcS[Calcpt-0].declaration)
			CalcVAL.statement = &ast.DeclStmt{Decl: CalcS[Calcpt-0].declaration}
		}
	case 8:
		//line calc.y:114
		{
			fmt.Println("assigned --> stmt")
			CalcVAL.statement = &ast.AssignStmt{
				Ident: CalcS[Calcpt-3].expression,
				Op:    CalcS[Calcpt-2].token.TokenType,
				X:     CalcS[Calcpt-1].expression,
			}

		}
	case 9:
		//line calc.y:124
		{
			fmt.Println("comment")
			CalcVAL.statement = &ast.EmptyStmt{}
		}
	case 10:
		//line calc.y:129
		{
			// conflict
			fmt.Println("return stmt")
			CalcVAL.statement = &ast.ReturnStmt{
				X: CalcS[Calcpt-0].expression,
			}

		}
	case 11:
		//line calc.y:138
		{
			fmt.Println("if stmt with else")
			CalcVAL.statement = &ast.IfStmt{
				Cond: CalcS[Calcpt-3].expression,
				Body: &CalcS[Calcpt-2].statement_block,
				Else: &CalcS[Calcpt-0].statement_block,
			}
		}
	case 12:
		//line calc.y:147
		{
			fmt.Println("if stmt")
			CalcVAL.statement = &ast.IfStmt{
				Cond: CalcS[Calcpt-1].expression,
				Body: &CalcS[Calcpt-0].statement_block,
			}
		}
	case 13:
		//line calc.y:155
		{
			fmt.Println("for stmt")
			CalcVAL.statement = &ast.ForStmt{
				X:    CalcS[Calcpt-1].expression,
				Body: &CalcS[Calcpt-0].statement_block,
			}
		}
	case 14:
		//line calc.y:163
		{
			fmt.Println("stmt + new line")
			CalcVAL.statement = CalcS[Calcpt-1].statement
		}
	case 15:
		//line calc.y:169
		{
			fmt.Println("var")
			CalcVAL.declaration = &ast.VarDecl{
				Name: &CalcS[Calcpt-1].identifier,
				Type: CalcS[Calcpt-0].expression,
			}
		}
	case 16:
		//line calc.y:177
		{
			fmt.Println("func")
			CalcVAL.declaration = &ast.FuncDecl{
				Name:    &CalcS[Calcpt-4].identifier,
				RetType: CalcS[Calcpt-1].expression,
				Body:    &CalcS[Calcpt-0].statement_block,
			}
		}
	case 17:
		//line calc.y:186
		{
			fmt.Println("func")
			CalcVAL.declaration = &ast.FuncDecl{
				Name:    &CalcS[Calcpt-5].identifier,
				Params:  CalcS[Calcpt-3].field_list,
				RetType: CalcS[Calcpt-1].expression,
				Body:    &CalcS[Calcpt-0].statement_block,
			}
		}
	case 18:
		//line calc.y:196
		{
			fmt.Println("decl new line")
			CalcVAL.declaration = CalcS[Calcpt-1].declaration
		}
	case 19:
		//line calc.y:203
		{
			CalcVAL.field_list = []ast.Field{CalcS[Calcpt-0].field}
		}
	case 20:
		//line calc.y:207
		{
			CalcVAL.field_list = append(CalcS[Calcpt-2].field_list, CalcS[Calcpt-0].field)
		}
	case 21:
		//line calc.y:213
		{
			fmt.Println("field")
			CalcVAL.field = ast.Field{
				Name: &CalcS[Calcpt-1].identifier,
				Type: CalcS[Calcpt-0].expression,
			}
		}
	case 22:
		//line calc.y:223
		{
			fmt.Printf("expr <- LPAREN expr RPAREN\n")
			CalcVAL.expression = CalcS[Calcpt-1].expression
		}
	case 23:
		//line calc.y:228
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   &CalcS[Calcpt-3].identifier,
				OpT: CalcS[Calcpt-2].token,
				Y:   CalcS[Calcpt-1].expression,
			}
		}
	case 24:
		//line calc.y:236
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 25:
		//line calc.y:245
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 26:
		//line calc.y:254
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 27:
		//line calc.y:263
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 28:
		//line calc.y:272
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 29:
		//line calc.y:281
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 30:
		//line calc.y:289
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 31:
		//line calc.y:297
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 32:
		//line calc.y:305
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-0].expression,
				OpT: CalcS[Calcpt-1].token,
			}
		}
	case 33:
		//line calc.y:313
		{
			fmt.Println("identifier")
			CalcVAL.expression = &ast.Ident{
				Name: CalcS[Calcpt-0].token.Value,
				T:    CalcS[Calcpt-0].token,
			}
		}
	case 34:
		//line calc.y:321
		{
			fmt.Printf("expr <- number\n")
			CalcVAL.expression = CalcS[Calcpt-0].expression
		}
	case 35:
		//line calc.y:328
		{
			fmt.Println("identifier")
			CalcVAL.identifier = ast.Ident{
				Name: CalcS[Calcpt-0].token.Value,
				T:    CalcS[Calcpt-0].token,
			}
		}
	case 36:
		//line calc.y:338
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 37:
		//line calc.y:343
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 38:
		//line calc.y:348
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 39:
		//line calc.y:353
		{
			fmt.Println("array")
			CalcVAL.expression = &ast.ArrayType{
				Index: -1,
				At:    CalcS[Calcpt-0].expression,
			}
		}
	case 40:
		//line calc.y:361
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
	case 41:
		//line calc.y:375
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 42:
		//line calc.y:380
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 43:
		//line calc.y:387
		{
			CalcVAL.token = CalcS[Calcpt-0].token
		}
	}
	goto Calcstack /* stack new state and value */
}
