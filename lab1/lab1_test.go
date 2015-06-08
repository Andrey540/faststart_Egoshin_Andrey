package main

import (
	"testing"
)

func TestAnalizeUserMassage(t *testing.T) {
	var message string;
	message = "what a good day and so evil floor! So nice!"
    bad, good, neutral := AnalizeUserMassage(message)
    if bad != 25 {
        t.Error("Expected bad 25, got ", bad)
    }
	if good != 50 {
        t.Error("Expected good 50, got ", good)
    }
	if neutral != 25 {
        t.Error("Expected neutral 25, got ", neutral)
    }
}
