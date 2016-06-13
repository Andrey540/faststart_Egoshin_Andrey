package main

import (
//	"os"
//	"bufio"
//	"stackmachine"
	"lexer"
	"fmt"
)

func main() {
/*	fi := bufio.NewReader(os.Stdin)
	stackmachineObj := new(stackmachine.StackMachine)
	stackmachineObj.Execute(fi);
	stackmachineObj.PrintStackAll();*/
	
	buffer := "x = 1 + 3  \n y = 2 - 3  "
	fmt.Println(buffer)
	lexerObj := new(lexer.Lexer)
	tokensParsed, _ := lexerObj.ParseTokens(buffer)
	fmt.Println(tokensParsed)
}