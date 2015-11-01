package main

import (
	"regexp"
	"fmt"
	"strconv"
)

type Calculator struct {
}


func (self *Calculator) parseAtom(tokens []string, index int) float64 {
	re := regexp.MustCompile(`^([0-9]+\.[0-9]+)|([0-9]+)`)
	if len(tokens) - 1 < index  ||
	    len(re.FindString(tokens[index])) == 0 {
		panic(fmt.Sprintf(self.prepareErrorMessage(tokens, index)))
	}
	f, err := strconv.ParseFloat(tokens[index], 64)
	if err != nil {
		panic(fmt.Sprintf(self.prepareErrorMessage(tokens, index)))
	}
	return f;
}

func (self *Calculator) parseMulDiv(tokens []string, index int) (float64, int) {
	l := self.parseAtom(tokens, index)
	op := self.getOperator(tokens, index + 1)
	if op == "*" {
		r, index := self.parseMulDiv(tokens, index + 2)
		return l * r, index
	} else if op == "/" {
		r,index := self.parseMulDiv(tokens, index + 2)
		return l / r, index
	} 
	return l, index	
}

func (self *Calculator) parseSum(tokens []string, index int) (float64, int) {
	l, index := self.parseMulDiv(tokens, index)
	fmt.Printf("%v", index)
	op := self.getOperator(tokens, index + 1)
	if op == "+" {
		r, index := self.parseMulDiv(tokens, index + 2)
		return l + r, index
	} else if op == "-" {
		r, index := self.parseMulDiv(tokens, index + 2)
		return l - r, index
	} else if op != "" {
		panic(fmt.Sprintf(self.prepareErrorMessage(tokens, index)))
	}
	return l, index
}

func (self *Calculator) getOperator(tokens []string, index int) string {
	if len(tokens) - 1 < index {
		return "";
	}
	return tokens[index]
}

func (self *Calculator) prepareErrorMessage(tokens []string, index int) string {
	result := "";
	for i := index; i < len(tokens); i++ {
		result += tokens[i]
	}
	return result
}

func (self *Calculator) calculate(expression string) (result float64, errorMessage string) {	
    defer func() {
        if err := recover(); err != nil {
		    errorMessage = err.(string)
        }
    }()
	
	re := regexp.MustCompile(`\*|\+|-|/|[\S^\*\+-/]+`)
	tokens := re.FindAllString(expression, -1)

	result, _ = self.parseSum(tokens, 0)

	return result, errorMessage
}