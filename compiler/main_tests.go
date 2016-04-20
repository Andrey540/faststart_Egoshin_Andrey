// +build with_tests

package main

import (
	"fmt"
	"lexer"
	"testing"
	"token"
	"reflect"
)

func TestCase1(context *testing.B) {
	context.ResetTimer();
	lexerObj := new(lexer.Lexer)

	var expectedTokens []token.Token
	var exepectedErrors []lexer.Error
	tokens, errors := lexerObj.ParseTokens("  1 2  ")

	tokenElem := token.Token {
		RowIndex: 0,
		ColumnIndex: 2,
		TokenType: token.INT_NUMBER,
		Value: "1",
	}
	expectedTokens = append(expectedTokens, tokenElem)

	tokenElem = token.Token {
		RowIndex: 0,
		ColumnIndex: 4,
		TokenType: token.INT_NUMBER,
		Value: "2",
	}

	expectedTokens = append(expectedTokens, tokenElem)

	if reflect.DeepEqual(expectedTokens, tokens) && reflect.DeepEqual(exepectedErrors, errors) {
		fmt.Println("success1")
	} else {
		fmt.Println("fail1")
	}
	context.ReportAllocs()
}

func TestCase2(context *testing.B) {
	context.ResetTimer();
	lexerObj := new(lexer.Lexer)

	var expectedTokens []token.Token
	var exepectedErrors []lexer.Error
	tokens, errors := lexerObj.ParseTokens("var index int")

	tokenElem := token.Token {
		RowIndex: 0,
		ColumnIndex: 0,
		TokenType: token.VAR,
		Value: "var",
	}
	expectedTokens = append(expectedTokens, tokenElem)

	tokenElem = token.Token {
		RowIndex: 0,
		ColumnIndex: 4,
		TokenType: token.IDENTIFIER,
		Value: "index",
	}
	expectedTokens = append(expectedTokens, tokenElem)

	tokenElem = token.Token {
		RowIndex: 0,
		ColumnIndex: 10,
		TokenType: token.INT,
		Value: "int",
	}
	expectedTokens = append(expectedTokens, tokenElem)

	if reflect.DeepEqual(expectedTokens, tokens) && reflect.DeepEqual(exepectedErrors, errors) {
		fmt.Println("success2")
	} else {
		fmt.Println("fail2")
	}
	context.ReportAllocs()
}

func main() {
	testing.Benchmark(TestCase1)
	testing.Benchmark(TestCase2)
}


