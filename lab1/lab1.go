package main

import (
	"bufio"
    "fmt"
    "os"
	"strings"
)

func AnalizeUserMassage(userMessage string)(bad, good, neutral float64){
	badWords := []string{"bad", "mad", "evil", "foolish"}
	badStatistic := 0	
	for i := 0; i < len(badWords); i++ {		
		if strings.Contains(userMessage, badWords[i]){
			badStatistic++
		}
	}		
	goodWords := []string{"good", "clever", "kind", "nice"}
	goodStatistic := 0
	for i := 0; i < len(goodWords); i++ {
		if strings.Contains(userMessage, goodWords[i]){
			goodStatistic++
		}
	}
	neutralWords := []string{"neutral", "car", "floor", "door"}
	neutralStatistic := 0
	for i := 0; i < len(neutralWords); i++ {
		if strings.Contains(userMessage, neutralWords[i]){
			neutralStatistic++
		}
	}
	sum := badStatistic + goodStatistic + neutralStatistic
	if sum == 0{
		sum = 1
	}
	
	bad = float64(badStatistic) / float64(sum) * 100
	good = float64(goodStatistic) / float64(sum) * 100
	neutral = float64(neutralStatistic) / float64(sum) * 100
	
	return bad, good, neutral
}

func main() {
	reader := bufio.NewReader(os.Stdin)
    fmt.Print("Enter text: ")
    userMessage, err := reader.ReadString('\n')
	if err != nil {
		fmt.Println("Input text error!")
		return
	}
	bad, good, neutral := AnalizeUserMassage(userMessage)
	fmt.Printf("bad statistic: %g", bad)
	fmt.Println("%")
	fmt.Printf("good statistic: %g", good)
	fmt.Println("%")
	fmt.Printf("neutral statistic: %g", neutral)
	fmt.Println("%")
}
