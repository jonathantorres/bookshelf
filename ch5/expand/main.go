package main

// Exercise 5.9

import (
	"fmt"
	"strings"
	"unicode"
)

func main() {
	txt := "This is a message, my name is $name!"
	fmt.Println(expand(txt, myExp))
}

func myExp(token string) string {
	return strings.ToUpper(token)
}

func expand(s string, f func(string) string) string {
	var token []byte
	dollarFound := false
	for _, let := range s {
		if dollarFound && unicode.IsLetter(let) {
			token = append(token, byte(let))
		} else {
			if let == '$' {
				dollarFound = true
				continue
			}
		}
	}
	return strings.Replace(s, "$"+string(token), f(string(token)), -1)
}
