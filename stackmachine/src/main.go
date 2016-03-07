package main

import (
	"os"
	"bufio"
	"stackmachine"
)

func main() {
	fi := bufio.NewReader(os.Stdin)
	stackmachineObj := new(stackmachine.StackMachine)
	stackmachineObj.Execute(fi);
	stackmachineObj.PrintStackAll();
}