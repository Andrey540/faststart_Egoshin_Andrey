//line calc.y:8
package main

import __yyfmt__ "fmt"

//line calc.y:9
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
const PRINT = 57353
const FUNC = 57354
const COMMENT = 57355
const LBRACK = 57356
const RBRACK = 57357
const COMMA = 57358
const INT_NUMBER = 57359
const FLOAT_NUMBER = 57360
const STRING_VALUE = 57361
const INT = 57362
const FLOAT = 57363
const STRING = 57364
const NEW_LINE = 57365
const VAR = 57366
const ASSIGNED = 57367
const IDENTIFIER = 57368
const ADD = 57369
const SUB = 57370
const MUL = 57371
const QUO = 57372
const REM = 57373
const SIN = 57374
const COS = 57375
const SQRT = 57376
const LPAREN = 57377
const RPAREN = 57378
const EQUAL = 57379
const NOT_EQUAL = 57380
const GREATE = 57381
const AND = 57382
const OR = 57383
const LESS = 57384
const UMINUS = 57385

var CalcToknames = [...]string{
	"$end",
	"error",
	"$unk",
	"EOF",
	"LBRACE",
	"RBRACE",
	"IF",
	"ELSE",
	"FOR",
	"RETURN",
	"PRINT",
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
	"LESS",
	"UMINUS",
}
var CalcStatenames = [...]string{}

const CalcEofCode = 1
const CalcErrCode = 2
const CalcInitialStackSize = 16

//line calc.y:444

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
	tokenMap[int(token.PRINT)] = PRINT
	tokenMap[int(token.RETURN)] = RETURN
	tokenMap[int(token.FUNC)] = FUNC
	tokenMap[int(token.COMMENT)] = COMMENT
	tokenMap[int(token.LBRACK)] = LBRACK
	tokenMap[int(token.RBRACK)] = RBRACK
	tokenMap[int(token.COMMA)] = COMMA
	tokenMap[int(token.EQUAL)] = EQUAL
	tokenMap[int(token.NOT_EQUAL)] = NOT_EQUAL
	tokenMap[int(token.GREATE)] = GREATE
	tokenMap[int(token.LESS)] = LESS
	tokenMap[int(token.STRING_VALUE)] = STRING_VALUE
	tokenMap[int(token.AND)] = AND
	tokenMap[int(token.OR)] = OR

	return tokenMap
}

func main() {

	defer func() {
		if err := recover(); err != nil {
			switch x := err.(type) {
			case string:
				fmt.Println(x)
			case error:
				fmt.Println(x.Error())
			default:
				fmt.Println("Unknown error")
			}
		}
	}()

	if len(os.Args) < 2 {
		panic("Missing parameter, provide file name!")
	}
	if len(os.Args) < 3 {
		panic("Missing parameter, provide otput file name!")
	}

	if buffer, ok := readFile(); ok {
		lexerObj := new(lexer.Lexer)
		tokensParsed, errors := lexerObj.ParseTokens(buffer)
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
		llvmBuilder.OutputFile = os.Args[2]
		mainResult.Accept(llvmBuilder)
	} else {
		fmt.Println("Error reading file")
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
	f, err := os.Open(os.Args[1])
	//	f, err := os.Open("example1.txt")
	if err != nil {
		return "", false
	}
	io.Copy(buf, f)
	f.Close()
	return string(buf.Bytes()), true
}

//line yacctab:1
var CalcExca = [...]int{
	-1, 1,
	1, -1,
	-2, 0,
}

const CalcNprod = 56
const CalcPrivate = 57344

var CalcTokenNames []string
var CalcStates []string

const CalcLast = 303

var CalcAct = [...]int{

	40, 31, 60, 61, 62, 63, 70, 80, 79, 78,
	9, 111, 64, 65, 66, 68, 69, 67, 60, 61,
	62, 63, 70, 16, 58, 4, 9, 110, 64, 65,
	66, 68, 69, 67, 38, 36, 20, 3, 76, 19,
	54, 55, 7, 71, 72, 73, 74, 75, 9, 35,
	51, 25, 81, 107, 48, 49, 50, 46, 99, 77,
	82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
	92, 93, 57, 108, 105, 94, 95, 97, 100, 101,
	102, 103, 60, 61, 62, 63, 70, 106, 62, 63,
	70, 109, 64, 65, 66, 68, 69, 67, 28, 60,
	61, 62, 63, 70, 17, 32, 19, 112, 113, 64,
	65, 66, 68, 69, 67, 104, 21, 37, 27, 60,
	61, 62, 63, 70, 60, 61, 62, 63, 70, 64,
	65, 66, 68, 69, 67, 60, 61, 62, 63, 70,
	32, 22, 53, 1, 96, 64, 65, 66, 68, 69,
	67, 6, 39, 2, 5, 98, 52, 0, 18, 4,
	0, 0, 60, 61, 62, 63, 70, 0, 0, 0,
	34, 3, 64, 65, 66, 68, 69, 67, 59, 15,
	60, 61, 62, 63, 70, 12, 13, 14, 0, 0,
	64, 65, 66, 68, 69, 67, 60, 61, 62, 63,
	70, 0, 0, 0, 0, 0, 64, 65, 66, 68,
	69, 67, 56, 44, 0, 45, 42, 43, 4, 41,
	0, 0, 0, 19, 54, 55, 0, 0, 0, 0,
	3, 0, 9, 0, 51, 0, 0, 0, 48, 49,
	50, 46, 44, 0, 45, 42, 43, 4, 41, 0,
	0, 0, 19, 54, 55, 0, 0, 0, 0, 3,
	0, 9, 0, 51, 19, 54, 55, 48, 49, 50,
	46, 0, 47, 9, 11, 51, 8, 10, 0, 48,
	49, 50, 46, 0, 0, 0, 0, 0, 0, 23,
	0, 0, 24, 0, 0, 26, 0, 0, 29, 0,
	30, 23, 33,
}
var CalcPact = [...]int{

	13, 147, 19, -16, -16, 19, -1000, -1000, 165, -1000,
	-12, -1000, -1000, -1000, -1000, 89, 0, 165, 36, -1000,
	165, 82, -1000, 165, -1000, 165, 100, 165, -16, -1000,
	-1000, -1000, 26, 100, -1000, 235, -1000, 206, 1, 19,
	153, -1000, 247, 247, 247, 247, 247, 24, -26, -27,
	-28, 247, -1000, -1000, -1000, -1000, -1000, 1, -1000, 247,
	247, 247, 247, 247, 247, 247, 247, 247, 247, 247,
	247, 169, 169, 135, 135, 108, 247, 22, 247, 247,
	247, -1000, 92, 59, 59, -1000, -1000, 97, 97, 97,
	97, 97, 97, -1000, 66, -1000, -1000, 72, 37, -1000,
	169, 55, -9, -25, -1000, 100, -1000, 247, -1000, -1000,
	-1000, -1000, -1000, 169,
}
var CalcPgo = [...]int{

	0, 142, 0, 156, 274, 155, 152, 272, 143, 34,
	117, 1, 141, 116,
}
var CalcR1 = [...]int{

	0, 8, 8, 8, 11, 10, 10, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 6, 6, 6, 6,
	13, 13, 12, 5, 5, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 7, 4, 4, 4,
	4, 4, 3, 3, 3, 1,
}
var CalcR2 = [...]int{

	0, 1, 2, 2, 4, 1, 2, 1, 4, 1,
	2, 2, 5, 3, 3, 2, 3, 6, 7, 2,
	1, 3, 2, 1, 3, 3, 4, 4, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 2, 1, 1, 1, 1, 1, 1,
	3, 4, 1, 1, 1, 1,
}
var CalcChk = [...]int{

	-1000, -8, -6, 24, 12, -6, 4, 23, -7, 26,
	-7, -4, 20, 21, 22, 14, 35, 15, -1, 17,
	36, -13, -12, -7, -4, 15, -4, 36, 16, -4,
	-4, -11, 5, -4, -12, 23, -11, -10, -9, -6,
	-2, 13, 10, 11, 7, 9, 35, -7, 32, 33,
	34, 28, -3, -1, 18, 19, 6, -9, 23, 25,
	27, 28, 29, 30, 37, 38, 39, 42, 40, 41,
	31, -2, -2, -2, -2, -2, 14, 35, 35, 35,
	35, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -11, -11, 36, -2, -5, 36,
	-2, -2, -2, -2, 23, 8, 15, 16, 36, 36,
	36, 36, -11, -2,
}
var CalcDef = [...]int{

	0, -2, 1, 0, 0, 2, 3, 19, 0, 46,
	0, 16, 47, 48, 49, 0, 0, 0, 0, 55,
	0, 0, 20, 0, 50, 0, 0, 0, 0, 22,
	51, 17, 0, 0, 21, 0, 18, 0, 5, 7,
	0, 9, 0, 0, 0, 0, 0, 44, 0, 0,
	0, 0, 45, 52, 53, 54, 4, 6, 15, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 10, 11, 0, 0, 0, 0, 0, 0, 0,
	0, 43, 0, 29, 30, 31, 32, 33, 34, 35,
	36, 37, 38, 39, 13, 14, 25, 0, 0, 28,
	23, 0, 0, 0, 8, 0, 26, 0, 27, 40,
	41, 42, 12, 24,
}
var CalcTok1 = [...]int{

	1,
}
var CalcTok2 = [...]int{

	2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
	12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
	22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
	42, 43,
}
var CalcTok3 = [...]int{
	0,
}

var CalcErrorMessages = [...]struct {
	state int
	token int
	msg   string
}{}

//line yaccpar:1

/*	parser for yacc output	*/

var (
	CalcDebug        = 0
	CalcErrorVerbose = false
)

type CalcLexer interface {
	Lex(lval *CalcSymType) int
	Error(s string)
}

type CalcParser interface {
	Parse(CalcLexer) int
	Lookahead() int
}

type CalcParserImpl struct {
	lval  CalcSymType
	stack [CalcInitialStackSize]CalcSymType
	char  int
}

func (p *CalcParserImpl) Lookahead() int {
	return p.char
}

func CalcNewParser() CalcParser {
	return &CalcParserImpl{}
}

const CalcFlag = -1000

func CalcTokname(c int) string {
	if c >= 1 && c-1 < len(CalcToknames) {
		if CalcToknames[c-1] != "" {
			return CalcToknames[c-1]
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

func CalcErrorMessage(state, lookAhead int) string {
	const TOKSTART = 4

	if !CalcErrorVerbose {
		return "syntax error"
	}

	for _, e := range CalcErrorMessages {
		if e.state == state && e.token == lookAhead {
			return "syntax error: " + e.msg
		}
	}

	res := "syntax error: unexpected " + CalcTokname(lookAhead)

	// To match Bison, suggest at most four expected tokens.
	expected := make([]int, 0, 4)

	// Look for shiftable tokens.
	base := CalcPact[state]
	for tok := TOKSTART; tok-1 < len(CalcToknames); tok++ {
		if n := base + tok; n >= 0 && n < CalcLast && CalcChk[CalcAct[n]] == tok {
			if len(expected) == cap(expected) {
				return res
			}
			expected = append(expected, tok)
		}
	}

	if CalcDef[state] == -2 {
		i := 0
		for CalcExca[i] != -1 || CalcExca[i+1] != state {
			i += 2
		}

		// Look for tokens that we accept or reduce.
		for i += 2; CalcExca[i] >= 0; i += 2 {
			tok := CalcExca[i]
			if tok < TOKSTART || CalcExca[i+1] == 0 {
				continue
			}
			if len(expected) == cap(expected) {
				return res
			}
			expected = append(expected, tok)
		}

		// If the default action is to accept or reduce, give up.
		if CalcExca[i+1] != 0 {
			return res
		}
	}

	for i, tok := range expected {
		if i == 0 {
			res += ", expecting "
		} else {
			res += " or "
		}
		res += CalcTokname(tok)
	}
	return res
}

func Calclex1(lex CalcLexer, lval *CalcSymType) (char, token int) {
	token = 0
	char = lex.Lex(lval)
	if char <= 0 {
		token = CalcTok1[0]
		goto out
	}
	if char < len(CalcTok1) {
		token = CalcTok1[char]
		goto out
	}
	if char >= CalcPrivate {
		if char < CalcPrivate+len(CalcTok2) {
			token = CalcTok2[char-CalcPrivate]
			goto out
		}
	}
	for i := 0; i < len(CalcTok3); i += 2 {
		token = CalcTok3[i+0]
		if token == char {
			token = CalcTok3[i+1]
			goto out
		}
	}

out:
	if token == 0 {
		token = CalcTok2[1] /* unknown char */
	}
	if CalcDebug >= 3 {
		__yyfmt__.Printf("lex %s(%d)\n", CalcTokname(token), uint(char))
	}
	return char, token
}

func CalcParse(Calclex CalcLexer) int {
	return CalcNewParser().Parse(Calclex)
}

func (Calcrcvr *CalcParserImpl) Parse(Calclex CalcLexer) int {
	var Calcn int
	var CalcVAL CalcSymType
	var CalcDollar []CalcSymType
	_ = CalcDollar // silence set and not used
	CalcS := Calcrcvr.stack[:]

	Nerrs := 0   /* number of errors */
	Errflag := 0 /* error recovery flag */
	Calcstate := 0
	Calcrcvr.char = -1
	Calctoken := -1 // Calcrcvr.char translated into internal numbering
	defer func() {
		// Make sure we report no lookahead when not parsing.
		Calcstate = -1
		Calcrcvr.char = -1
		Calctoken = -1
	}()
	Calcp := -1
	goto Calcstack

ret0:
	return 0

ret1:
	return 1

Calcstack:
	/* put a state and value onto the stack */
	if CalcDebug >= 4 {
		__yyfmt__.Printf("char %v in %v\n", CalcTokname(Calctoken), CalcStatname(Calcstate))
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
	if Calcrcvr.char < 0 {
		Calcrcvr.char, Calctoken = Calclex1(Calclex, &Calcrcvr.lval)
	}
	Calcn += Calctoken
	if Calcn < 0 || Calcn >= CalcLast {
		goto Calcdefault
	}
	Calcn = CalcAct[Calcn]
	if CalcChk[Calcn] == Calctoken { /* valid shift */
		Calcrcvr.char = -1
		Calctoken = -1
		CalcVAL = Calcrcvr.lval
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
		if Calcrcvr.char < 0 {
			Calcrcvr.char, Calctoken = Calclex1(Calclex, &Calcrcvr.lval)
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
			if Calcn < 0 || Calcn == Calctoken {
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
			Calclex.Error(CalcErrorMessage(Calcstate, Calctoken))
			Nerrs++
			if CalcDebug >= 1 {
				__yyfmt__.Printf("%s", CalcStatname(Calcstate))
				__yyfmt__.Printf(" saw %s\n", CalcTokname(Calctoken))
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
				__yyfmt__.Printf("error recovery discards %s\n", CalcTokname(Calctoken))
			}
			if Calctoken == CalcEofCode {
				goto ret1
			}
			Calcrcvr.char = -1
			Calctoken = -1
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
	// Calcp is now the index of $0. Perform the default action. Iff the
	// reduced production is ε, $1 is possibly out of range.
	if Calcp+1 >= len(CalcS) {
		nyys := make([]CalcSymType, len(CalcS)*2)
		copy(nyys, CalcS)
		CalcS = nyys
	}
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
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:79
		{
			CalcVAL.file = ast.FileAst{Decls: []ast.Declaration{CalcDollar[1].declaration}}
		}
	case 2:
		CalcDollar = CalcS[Calcpt-2 : Calcpt+1]
		//line calc.y:83
		{
			CalcDollar[1].file.Decls = append(CalcDollar[1].file.Decls, CalcDollar[2].declaration)
			CalcVAL.file = CalcDollar[1].file
		}
	case 3:
		CalcDollar = CalcS[Calcpt-2 : Calcpt+1]
		//line calc.y:88
		{
			mainResult = CalcDollar[1].file
		}
	case 4:
		CalcDollar = CalcS[Calcpt-4 : Calcpt+1]
		//line calc.y:93
		{
			blockstmts = append(blockstmts, CalcDollar[3].statement_list)
			CalcVAL.statement_block = len(blockstmts) - 1
		}
	case 5:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:100
		{
			CalcVAL.statement_list = ast.BlockStmt{List: []ast.Statement{CalcDollar[1].statement}}
		}
	case 6:
		CalcDollar = CalcS[Calcpt-2 : Calcpt+1]
		//line calc.y:104
		{
			CalcDollar[1].statement_list.List = append(CalcDollar[1].statement_list.List, CalcDollar[2].statement)
			CalcVAL.statement_list = CalcDollar[1].statement_list
		}
	case 7:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:110
		{
			CalcVAL.statement = &ast.DeclStmt{Decl: CalcDollar[1].declaration}
		}
	case 8:
		CalcDollar = CalcS[Calcpt-4 : Calcpt+1]
		//line calc.y:114
		{
			CalcVAL.statement = &ast.AssignStmt{
				Ident: CalcDollar[1].expression,
				Op:    CalcDollar[2].token.TokenType,
				X:     CalcDollar[3].expression,
			}

		}
	case 9:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:123
		{
			CalcVAL.statement = &ast.EmptyStmt{}
		}
	case 10:
		CalcDollar = CalcS[Calcpt-2 : Calcpt+1]
		//line calc.y:127
		{
			// conflict
			CalcVAL.statement = &ast.ReturnStmt{
				X: CalcDollar[2].expression,
			}

		}
	case 11:
		CalcDollar = CalcS[Calcpt-2 : Calcpt+1]
		//line calc.y:135
		{
			// conflict
			CalcVAL.statement = &ast.PrintStmt{
				X: CalcDollar[2].expression,
			}

		}
	case 12:
		CalcDollar = CalcS[Calcpt-5 : Calcpt+1]
		//line calc.y:143
		{
			CalcVAL.statement = &ast.IfStmt{
				Cond: CalcDollar[2].expression,
				Body: &blockstmts[CalcDollar[3].statement_block],
				Else: &blockstmts[CalcDollar[5].statement_block],
			}
		}
	case 13:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:151
		{
			CalcVAL.statement = &ast.IfStmt{
				Cond: CalcDollar[2].expression,
				Body: &blockstmts[CalcDollar[3].statement_block],
			}
		}
	case 14:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:158
		{
			CalcVAL.statement = &ast.ForStmt{
				X:    CalcDollar[2].expression,
				Body: &blockstmts[CalcDollar[3].statement_block],
			}
		}
	case 15:
		CalcDollar = CalcS[Calcpt-2 : Calcpt+1]
		//line calc.y:165
		{
			CalcVAL.statement = CalcDollar[1].statement
		}
	case 16:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:171
		{
			CalcVAL.declaration = &ast.VarDecl{
				Name: &identifiers[CalcDollar[2].identifier],
				Type: CalcDollar[3].expression,
			}
		}
	case 17:
		CalcDollar = CalcS[Calcpt-6 : Calcpt+1]
		//line calc.y:178
		{
			CalcVAL.declaration = &ast.FuncDecl{
				Name:    &identifiers[CalcDollar[2].identifier],
				RetType: CalcDollar[5].expression,
				Body:    &blockstmts[CalcDollar[6].statement_block],
			}
		}
	case 18:
		CalcDollar = CalcS[Calcpt-7 : Calcpt+1]
		//line calc.y:186
		{
			CalcVAL.declaration = &ast.FuncDecl{
				Name:    &identifiers[CalcDollar[2].identifier],
				Params:  CalcDollar[4].field_list,
				RetType: CalcDollar[6].expression,
				Body:    &blockstmts[CalcDollar[7].statement_block],
			}
		}
	case 19:
		CalcDollar = CalcS[Calcpt-2 : Calcpt+1]
		//line calc.y:195
		{
			CalcVAL.declaration = CalcDollar[1].declaration
		}
	case 20:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:201
		{
			CalcVAL.field_list = []ast.Field{CalcDollar[1].field}
		}
	case 21:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:205
		{
			CalcVAL.field_list = append(CalcDollar[1].field_list, CalcDollar[3].field)
		}
	case 22:
		CalcDollar = CalcS[Calcpt-2 : Calcpt+1]
		//line calc.y:211
		{
			CalcVAL.field = ast.Field{
				Name: &identifiers[CalcDollar[1].identifier],
				Type: CalcDollar[2].expression,
			}
		}
	case 23:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:220
		{
			CalcVAL.expression_list = []ast.Expression{CalcDollar[1].expression}
		}
	case 24:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:224
		{
			CalcVAL.expression_list = append(CalcDollar[1].expression_list, CalcDollar[3].expression)
		}
	case 25:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:230
		{
			CalcVAL.expression = CalcDollar[2].expression
		}
	case 26:
		CalcDollar = CalcS[Calcpt-4 : Calcpt+1]
		//line calc.y:234
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   &identifiers[CalcDollar[1].identifier],
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 27:
		CalcDollar = CalcS[Calcpt-4 : Calcpt+1]
		//line calc.y:242
		{
			// conflict
			CalcVAL.expression = &ast.CallExpr{
				Fun:  &identifiers[CalcDollar[1].identifier],
				Args: CalcDollar[3].expression_list,
			}
		}
	case 28:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:250
		{
			CalcVAL.expression = &ast.CallExpr{
				Fun: &identifiers[CalcDollar[1].identifier],
			}
		}
	case 29:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:256
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 30:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:264
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 31:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:272
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 32:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:280
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 33:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:288
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 34:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:296
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 35:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:304
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 36:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:312
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 37:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:320
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 38:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:328
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 39:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:336
		{
			CalcVAL.expression = &ast.BinaryExpr{
				X:   CalcDollar[1].expression,
				OpT: CalcDollar[2].token,
				Y:   CalcDollar[3].expression,
			}
		}
	case 40:
		CalcDollar = CalcS[Calcpt-4 : Calcpt+1]
		//line calc.y:344
		{
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcDollar[3].expression,
				OpT: CalcDollar[1].token,
			}
		}
	case 41:
		CalcDollar = CalcS[Calcpt-4 : Calcpt+1]
		//line calc.y:351
		{
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcDollar[3].expression,
				OpT: CalcDollar[1].token,
			}
		}
	case 42:
		CalcDollar = CalcS[Calcpt-4 : Calcpt+1]
		//line calc.y:358
		{
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcDollar[3].expression,
				OpT: CalcDollar[1].token,
			}
		}
	case 43:
		CalcDollar = CalcS[Calcpt-2 : Calcpt+1]
		//line calc.y:365
		{
			CalcVAL.expression = &ast.UnaryExpr{
				X:   CalcDollar[2].expression,
				OpT: CalcDollar[1].token,
			}
		}
	case 44:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:372
		{
			CalcVAL.expression = &identifiers[CalcDollar[1].identifier]
		}
	case 45:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:376
		{
			CalcVAL.expression = CalcDollar[1].expression
		}
	case 46:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:382
		{
			ident := ast.Ident{
				Name: CalcDollar[1].token.Value,
				T:    CalcDollar[1].token,
			}
			identifiers = append(identifiers, ident)
			CalcVAL.identifier = len(identifiers) - 1
		}
	case 47:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:393
		{
			CalcVAL.expression = &ast.BasicLit{T: CalcDollar[1].token}
		}
	case 48:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:397
		{
			CalcVAL.expression = &ast.BasicLit{T: CalcDollar[1].token}
		}
	case 49:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:401
		{
			CalcVAL.expression = &ast.BasicLit{T: CalcDollar[1].token}
		}
	case 50:
		CalcDollar = CalcS[Calcpt-3 : Calcpt+1]
		//line calc.y:405
		{
			CalcVAL.expression = &ast.ArrayType{
				Index: 0,
				At:    CalcDollar[3].expression,
			}
		}
	case 51:
		CalcDollar = CalcS[Calcpt-4 : Calcpt+1]
		//line calc.y:412
		{
			value, err := strconv.ParseUint(CalcDollar[2].token.Value, 10, 64)
			if err != nil {
				panic(err)
			}
			CalcVAL.expression = &ast.ArrayType{
				Index: value,
				At:    CalcDollar[4].expression,
			}
		}
	case 52:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:425
		{
			CalcVAL.expression = &ast.BasicLit{T: CalcDollar[1].token}
		}
	case 53:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:429
		{
			CalcVAL.expression = &ast.BasicLit{T: CalcDollar[1].token}
		}
	case 54:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:433
		{
			CalcVAL.expression = &ast.BasicLit{T: CalcDollar[1].token}
		}
	case 55:
		CalcDollar = CalcS[Calcpt-1 : Calcpt+1]
		//line calc.y:439
		{
			CalcVAL.token = CalcDollar[1].token
		}
	}
	goto Calcstack /* stack new state and value */
}
