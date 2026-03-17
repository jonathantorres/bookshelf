package main

import (
	"fmt"
	"strings"
	"unicode"
)

var subs = map[string]string{
	"name":     "Jonathan",
	"hometown": "Puerto Rico",
	"age":      "35",
}

func main() {
	txt := "Hi, my name is $name and I'm from $hometown. I'm $age years old"
	fmt.Println(expand(txt, myExp))
}

func myExp(token string) string {
	if val, ok := subs[token]; ok {
		return val
	}
	return strings.ToUpper(token)
}

func expand(s string, f func(string) string) string {
	var tokens []byte
	dollarFound := false
	for _, let := range s {
		if dollarFound && unicode.IsLetter(let) {
			tokens = append(tokens, byte(let))
		} else {
			dollarFound = false
			if let == '$' {
				dollarFound = true
				tokens = append(tokens, '$')
				continue
			}
		}
	}
	expanded := s
	for _, tok := range strings.Split(string(tokens), "$") {
		if tok != "" {
			expanded = strings.Replace(expanded, "$"+tok, f(tok), -1)
		}
	}
	return expanded
}
