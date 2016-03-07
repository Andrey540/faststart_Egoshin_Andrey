package stackmachine

import (
	"fmt"
	"bufio"
	"errors"
	"io"
	"strconv"
)

const STACK_SIZE int = 1000;

type StackMachine struct {
	stack []int64
}

func (self *StackMachine)Execute(fi *bufio.Reader) {
	var valueStr string;
	var command string
    for {
		num, err := fmt.Fscanln(fi, &command, &valueStr)	
		if err == io.EOF {
			break
		}	
		switch num {
			case 0:
	            panic(errors.New("unexpected scan error"))
	        case 1:			
	            self.executeCommand(command)
	        case 2:
				value, err := strconv.ParseInt(valueStr, 10, 64)
				if err != nil {
					panic(err)
				}
				if command == "push" {
					self.push(value)
				} else {
					panic(errors.New("unexpected command " + command))
				}
				fmt.Println(value)
	    }  
    }
}

func (self *StackMachine)PrintStackAll() {
	fmt.Println("--- stack begin ---")
	for i, value := range self.stack {
        fmt.Printf("%d. %d\n", i, value)
    }
	fmt.Println("--- stack end ---")
}

func (self *StackMachine)PrintStackTop() {
    fmt.Printf("%d\n", self.stack[len(self.stack) - 1])
}

func (self *StackMachine)push(value int64) {
	if len(self.stack) >= STACK_SIZE {
		panic(errors.New("stack overflow"))
	}
	self.stack = append(self.stack, value)
}

func (self *StackMachine)pop() {
    self.check_underflow(0);
	self.stack = self.stack[0 : len(self.stack) - 1]
}

func (self *StackMachine)add() {
    self.check_underflow(1);
    self.stack[len(self.stack) - 2] = self.stack[len(self.stack) - 2] + self.stack[len(self.stack) - 1];
	self.stack = self.stack[0 : len(self.stack) - 1]
}

func (self *StackMachine)multiply() {
    self.check_underflow(1);
    self.stack[len(self.stack) - 2] = self.stack[len(self.stack) - 2] * self.stack[len(self.stack) - 1];
	self.stack = self.stack[0 : len(self.stack) - 1]
}

func (self *StackMachine)substract() {
    self.check_underflow(1);
    self.stack[len(self.stack) - 2] = self.stack[len(self.stack) - 2] - self.stack[len(self.stack) - 1];
	self.stack = self.stack[0 : len(self.stack) - 1]
}

func (self *StackMachine)divide() {
    self.check_underflow(1);
    self.stack[len(self.stack) - 2] = self.stack[len(self.stack) - 2] / self.stack[len(self.stack) - 1];
	self.stack = self.stack[0 : len(self.stack) - 1]
}

func (self *StackMachine)executeCommand(command string) {
	if command == "pop" {
		self.pop()
	} else if command == "add" {
		self.add()
	} else if command == "mul" {
		self.multiply()
	} else if command == "sub" {
		self.substract()
	} else if command == "div" {
		self.divide()
	} else {
		panic(errors.New("unexpected command " + command))
	}
}

func (self *StackMachine)check_underflow(reserve int) {
    if len(self.stack) < reserve {
		panic(errors.New("stack underflow"))
    }
}