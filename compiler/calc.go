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

var mainResult ast.BlockStmt

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

//line calc.y:402

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
	-1, 21,
	13, 33,
	-2, 31,
}

const CalcNprod = 42
const CalcPrivate = 57344

var CalcTokenNames []string
var CalcStates []string

const CalcLast = 195

var CalcAct = []int{

	1, 16, 40, 56, 23, 73, 61, 46, 84, 8,
	45, 40, 71, 44, 81, 39, 41, 28, 25, 24,
	36, 37, 38, 43, 29, 42, 21, 83, 20, 4,
	47, 6, 17, 18, 19, 15, 2, 27, 54, 55,
	48, 49, 50, 51, 52, 53, 3, 72, 31, 32,
	33, 34, 35, 63, 64, 65, 66, 78, 31, 32,
	33, 34, 35, 74, 69, 70, 25, 77, 5, 79,
	33, 34, 35, 80, 60, 82, 7, 22, 85, 57,
	58, 59, 0, 87, 3, 86, 74, 88, 68, 90,
	89, 26, 11, 0, 12, 10, 14, 9, 0, 0,
	0, 25, 24, 0, 0, 0, 0, 13, 0, 21,
	0, 20, 0, 0, 0, 17, 18, 19, 15, 11,
	0, 12, 10, 14, 9, 0, 0, 0, 25, 24,
	0, 0, 0, 0, 13, 0, 21, 0, 20, 0,
	0, 0, 17, 18, 19, 15, 31, 32, 33, 34,
	35, 0, 0, 0, 0, 76, 31, 32, 33, 34,
	35, 75, 67, 2, 0, 62, 31, 32, 33, 34,
	35, 0, 31, 32, 33, 34, 35, 31, 32, 33,
	34, 35, 0, 31, 32, 33, 34, 35, 30, 0,
	31, 32, 33, 34, 35,
}
var CalcPact = []int{

	31, 42, 8, -1000, 112, 85, -4, 3, 165, -1000,
	2, 2, 2, -13, -13, 2, 10, -20, -23, -26,
	2, -1000, -1000, -1000, -1000, -1000, -1000, -4, -1000, -1000,
	2, 2, 2, 2, 2, 2, 152, 158, 158, 61,
	-1000, -27, 131, 2, 2, 2, 2, -1000, 141, 43,
	43, -1000, -1000, -1000, 80, 42, -1000, -1000, -1000, -1000,
	50, -22, -1000, 147, 121, 33, 23, -1000, 31, 61,
	0, 61, -7, -1000, 61, -1000, -1000, -1000, -1000, 42,
	-1000, 61, 31, 61, -13, -1000, -1000, 42, 31, -1000,
	42,
}
var CalcPgo = []int{

	0, 4, 9, 77, 3, 76, 1, 31, 68, 0,
	5, 47,
}
var CalcR1 = []int{

	0, 9, 9, 8, 8, 7, 7, 7, 7, 7,
	7, 7, 7, 5, 5, 5, 5, 11, 11, 10,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 6, 4, 4, 4, 4, 4, 3,
	3, 1,
}
var CalcR2 = []int{

	0, 4, 2, 1, 2, 1, 4, 1, 2, 5,
	3, 3, 2, 3, 6, 7, 2, 1, 3, 2,
	3, 4, 3, 3, 3, 3, 3, 4, 4, 4,
	2, 1, 1, 1, 1, 1, 1, 3, 4, 1,
	1, 1,
}
var CalcChk = []int{

	-1000, -9, 5, 4, 21, -8, -7, -5, -2, 12,
	10, 7, 9, 22, 11, 33, -6, 30, 31, 32,
	26, 24, -3, -1, 17, 16, 6, -7, 21, 21,
	23, 25, 26, 27, 28, 29, -2, -2, -2, -6,
	24, -6, -2, 13, 33, 33, 33, -2, -2, -2,
	-2, -2, -2, -2, -9, -9, -4, 18, 19, 20,
	13, 33, 34, -2, -2, -2, -2, 21, 8, 14,
	-1, 34, -11, -10, -6, 14, 34, 34, 34, -9,
	-4, 14, -4, 34, 15, -4, -4, -9, -4, -10,
	-9,
}
var CalcDef = []int{

	0, -2, 0, 2, 0, 0, 3, 5, 0, 7,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, -2, 32, 39, 40, 41, 1, 4, 12, 16,
	0, 0, 0, 0, 0, 0, 8, 0, 0, 0,
	33, 0, 0, 0, 0, 0, 0, 30, 0, 22,
	23, 24, 25, 26, 10, 11, 13, 34, 35, 36,
	0, 0, 20, 0, 0, 0, 0, 6, 0, 0,
	0, 0, 0, 17, 0, 21, 27, 28, 29, 9,
	37, 0, 0, 0, 0, 19, 38, 14, 0, 18,
	15,
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
		//line calc.y:88
		{
			fmt.Println("init stmt block")
			CalcVAL.statement_block = CalcS[Calcpt-1].statement_block
		}
	case 2:
		//line calc.y:97
		{
			fmt.Println("EOF")
			mainResult = CalcS[Calcpt-1].statement_block
		}
	case 3:
		//line calc.y:104
		{
			fmt.Println("list statement begin")
			fmt.Println(CalcS[Calcpt-0].statement)
			CalcVAL.statement_block = ast.BlockStmt{List: []ast.Statement{CalcS[Calcpt-0].statement}}
		}
	case 4:
		//line calc.y:110
		{
			fmt.Println("add stmt to list")
			CalcS[Calcpt-1].statement_block.List = append(CalcS[Calcpt-1].statement_block.List, CalcS[Calcpt-0].statement)
			CalcVAL.statement_block = CalcS[Calcpt-1].statement_block
		}
	case 5:
		//line calc.y:117
		{
			fmt.Println("decl --> stmt")
			fmt.Println(CalcS[Calcpt-0].declaration)
			CalcVAL.statement = &ast.DeclStmt{Decl: CalcS[Calcpt-0].declaration}
		}
	case 6:
		//line calc.y:123
		{
			fmt.Println("assigned --> stmt")
			CalcVAL.statement = &ast.AssignStmt{
				Ident: CalcS[Calcpt-3].expression,
				Op:    CalcS[Calcpt-2].token.TokenType,
				X:     CalcS[Calcpt-1].expression,
			}

		}
	case 7:
		//line calc.y:133
		{
			fmt.Println("comment")
			CalcVAL.statement = &ast.EmptyStmt{}
		}
	case 8:
		//line calc.y:138
		{
			// conflict
			fmt.Println("return stmt")
			CalcVAL.statement = &ast.ReturnStmt{
				X: CalcS[Calcpt-0].expression,
			}

		}
	case 9:
		//line calc.y:147
		{
			fmt.Println("if stmt with else")
			CalcVAL.statement = &ast.IfStmt{
				Cond: CalcS[Calcpt-3].expression,
				Body: &CalcS[Calcpt-2].statement_block,
				Else: &CalcS[Calcpt-0].statement_block,
			}
		}
	case 10:
		//line calc.y:156
		{
			fmt.Println("if stmt")
			CalcVAL.statement = &ast.IfStmt{
				Cond: CalcS[Calcpt-1].expression,
				Body: &CalcS[Calcpt-0].statement_block,
			}
		}
	case 11:
		//line calc.y:164
		{
			fmt.Println("for stmt")
			CalcVAL.statement = &ast.ForStmt{
				X:    CalcS[Calcpt-1].expression,
				Body: &CalcS[Calcpt-0].statement_block,
			}
		}
	case 12:
		//line calc.y:172
		{
			fmt.Println("stmt new line")
			CalcVAL.statement = CalcS[Calcpt-1].statement
		}
	case 13:
		//line calc.y:179
		{
			fmt.Println("var")
			CalcVAL.declaration = &ast.VarDecl{
				Name: &CalcS[Calcpt-1].identifier,
				Type: CalcS[Calcpt-0].expression,
			}
		}
	case 14:
		//line calc.y:187
		{
			fmt.Println("func")
			CalcVAL.declaration = &ast.FuncDecl{
				Name:    &CalcS[Calcpt-4].identifier,
				RetType: CalcS[Calcpt-1].expression,
				Body:    &CalcS[Calcpt-0].statement_block,
			}
		}
	case 15:
		//line calc.y:196
		{
			fmt.Println("func")
			CalcVAL.declaration = &ast.FuncDecl{
				Name:    &CalcS[Calcpt-5].identifier,
				Params:  CalcS[Calcpt-3].field_list,
				RetType: CalcS[Calcpt-1].expression,
				Body:    &CalcS[Calcpt-0].statement_block,
			}
		}
	case 16:
		//line calc.y:206
		{
			fmt.Println("decl new line")
			CalcVAL.declaration = CalcS[Calcpt-1].declaration
		}
	case 17:
		//line calc.y:213
		{
			CalcVAL.field_list = []ast.Field{CalcS[Calcpt-0].field}
		}
	case 18:
		//line calc.y:217
		{
			CalcVAL.field_list = append(CalcS[Calcpt-2].field_list, CalcS[Calcpt-0].field)
		}
	case 19:
		//line calc.y:223
		{
			fmt.Println("field")
			CalcVAL.field = ast.Field{
				Name: &CalcS[Calcpt-1].identifier,
				Type: CalcS[Calcpt-0].expression,
			}
		}
	case 20:
		//line calc.y:233
		{
			fmt.Printf("expr <- LPAREN expr RPAREN\n")
			CalcVAL.expression = CalcS[Calcpt-1].expression
		}
	case 21:
		//line calc.y:238
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   &CalcS[Calcpt-3].identifier,
				OpT: CalcS[Calcpt-2].token,
				Y:   CalcS[Calcpt-1].expression,
			}
		}
	case 22:
		//line calc.y:246
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 23:
		//line calc.y:255
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 24:
		//line calc.y:264
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 25:
		//line calc.y:273
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 26:
		//line calc.y:282
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcS[Calcpt-2].expression,
				OpT: CalcS[Calcpt-1].token,
				Y:   CalcS[Calcpt-0].expression,
			}
		}
	case 27:
		//line calc.y:291
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 28:
		//line calc.y:299
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 29:
		//line calc.y:307
		{
			fmt.Println(CalcS[Calcpt-3].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-1].expression,
				OpT: CalcS[Calcpt-3].token,
			}
		}
	case 30:
		//line calc.y:315
		{
			fmt.Println(CalcS[Calcpt-1].token.Value)
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcS[Calcpt-0].expression,
				OpT: CalcS[Calcpt-1].token,
			}
		}
	case 31:
		//line calc.y:323
		{
			fmt.Println("identifier")
			CalcVAL.expression = &ast.Ident{
				Name: CalcS[Calcpt-0].token.Value,
				T:    CalcS[Calcpt-0].token,
			}
		}
	case 32:
		//line calc.y:331
		{
			fmt.Printf("expr <- number\n")
			CalcVAL.expression = CalcS[Calcpt-0].expression
		}
	case 33:
		//line calc.y:338
		{
			fmt.Println("identifier")
			CalcVAL.identifier = ast.Ident{
				Name: CalcS[Calcpt-0].token.Value,
				T:    CalcS[Calcpt-0].token,
			}
		}
	case 34:
		//line calc.y:348
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 35:
		//line calc.y:353
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 36:
		//line calc.y:358
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 37:
		//line calc.y:363
		{
			fmt.Println("array")
			CalcVAL.expression = &ast.ArrayType{
				Index: -1,
				At:    CalcS[Calcpt-0].expression,
			}
		}
	case 38:
		//line calc.y:371
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
	case 39:
		//line calc.y:385
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 40:
		//line calc.y:390
		{
			fmt.Println(CalcS[Calcpt-0].token.Value)
			CalcVAL.expression = &ast.BasicLit{T: CalcS[Calcpt-0].token}
		}
	case 41:
		//line calc.y:397
		{
			CalcVAL.token = CalcS[Calcpt-0].token
		}
	}
	goto Calcstack /* stack new state and value */
}
