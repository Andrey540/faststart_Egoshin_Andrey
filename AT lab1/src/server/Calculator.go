package main

import (
	"regexp"
	"strconv"
	"errors"
)

type Calculator struct {
	  atomReg *regexp.Regexp
}

func (self *Calculator) parseAtom(tokens []string, index int) float64 {
	if len(tokens) - 1 < index  ||
	    len(self.atomReg.FindString(tokens[index])) == 0 {
		panic(errors.New("Unexpected token " + self.prepareErrorMessage(tokens, index)))
	}
	f, err := strconv.ParseFloat(tokens[index], 64)
	if err != nil {
		panic(errors.New("Can not convert token to number " + self.prepareErrorMessage(tokens, index)))
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
	op := self.getOperator(tokens, index + 1)
	if op == "+" {
		r, index := self.parseSum(tokens, index + 2)
		return l + r, index
	} else if op == "-" {
		r, index := self.parseSum(tokens, index + 2)
		return l - r, index
	} else if op != "" {
		panic(errors.New("Unexpected operator " + self.prepareErrorMessage(tokens, index)))
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
			switch x := err.(type) {
	        case string:
	            errorMessage = x
	        case error:
	            errorMessage = x.Error()
	        default:
	            errorMessage = "Unknown error"
	        }    
        }
    }()
		
	re := regexp.MustCompile(`\*|\+|-|/|[^\*\+-/\s]+`)
	tokens := re.FindAllString(expression, -1)

	self.atomReg = regexp.MustCompile(`^([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*)|([0-9]+)$`)
	result, _ = self.parseSum(tokens, 0)

	return result, errorMessage
}