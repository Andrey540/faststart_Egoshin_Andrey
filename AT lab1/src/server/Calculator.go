package main

import (
	"regexp"
	"strconv"
	"errors"
	"math"
)

type Calculator struct {
	  atomReg *regexp.Regexp
}

func (self *Calculator) parseAtom(tokens []string, index int) (float64, int) {
	op := self.getOperator(tokens, index)
	var number = 0.0
	if op == "(" {
		number, index := self.parseExpression(tokens, index)
		return number, index
	} else {
		if len(tokens) - 1 < index  ||
		    len(self.atomReg.FindString(tokens[index])) == 0 {
			panic(errors.New("Unexpected token " + self.prepareErrorMessage(tokens, index)))
		}
		number, err := strconv.ParseFloat(tokens[index], 64)
		if err != nil {
			panic(errors.New("Can not convert token to number " + self.prepareErrorMessage(tokens, index)))
		}
		return number, index
	}
	return number, index
}

func (self *Calculator) parseMulDiv(tokens []string, index int) (float64, int) {
	l, index := self.parseMath(tokens, index)
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
	} else if op != "" && op != ")" {
		panic(errors.New("Unexpected operator " + self.prepareErrorMessage(tokens, index)))
	}
	return l, index
}

func (self *Calculator) parseMath(tokens []string, index int) (float64, int) {
	op := self.getOperator(tokens, index)
	if op == "sin" || op == "asin" || op == "cos" || op == "acos" || op == "sqrt" {
		opNext := self.getOperator(tokens, index + 1)
		if opNext != "(" {
			panic(errors.New("Expecte (, got " + opNext))
		}
		
		expBeginIndex := index;
		value, index := self.parseExpression(tokens, index + 1);
		if op == "sin" {
			value = math.Sin(value)
		} else if op == "asin" {
			value = math.Asin(value)
		} else if op == "cos" {
			value = math.Cos(value)
		} else if op == "acos" {
			value = math.Acos(value)
		}else if op == "sqrt" {
			if value < 0 {
				panic(errors.New("Expecte negative value of function " + self.prepareErrorMessage(tokens, expBeginIndex)))
			}
			value = math.Sqrt(value)
		}
		return value, index
	} 

	return self.parseAtom(tokens, index)
}

func (self *Calculator) parseExpression(tokens []string, index int) (float64, int) {
	op := self.getOperator(tokens, index)
	if op == "(" {
		l, index := self.parseSum(tokens, index + 1)
		op := self.getOperator(tokens, index + 1)
		if op != ")" {
			panic(errors.New("Expecte ), got " + op))
		}
		return l, index + 1
	}
	 
	return self.parseSum(tokens, index)
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
		
	re := regexp.MustCompile(`sin|asin|cos|acos|sqrt|\*|\+|-|/|\(|\)|[^\*\+-/\(\)\s]+`)
	tokens := re.FindAllString(expression, -1)

	self.atomReg = regexp.MustCompile(`^([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*)|([0-9]+)$`)
	result, _ = self.parseSum(tokens, 0)

	return result, errorMessage
}