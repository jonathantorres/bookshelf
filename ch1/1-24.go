package main

import (
	"bufio"
	"fmt"
	"os"
)

const maxLine = 1000

func main() {
	for {
		line, l := getLine(maxLine)
		var commErr bool
		var (
			parensL   int
			bracketsL int
			doubleQl  int
			singleQl  int
		)
		for i := 0; i < l; i++ {
			ch := rune(line[i])
			if ch == '(' || ch == ')' {
				parensL++
			}
			if ch == '[' || ch == ']' {
				bracketsL++
			}
			if ch == '"' {
				doubleQl++
			}
			if ch == '\'' {
				singleQl++
			}
			if ch == '/' && rune(line[i+1]) == '/' {
				break
			} else if ch == '/' {
				commErr = true
			}
		}
		if parensL%2 != 0 || bracketsL%2 != 0 || singleQl%2 != 0 || doubleQl%2 != 0 || commErr == true {
			fmt.Println("syntax error!")
		}
	}
}

func getLine(lim int) ([]byte, int) {
	var c byte
	var i int
	s := make([]byte, lim)
	r := bufio.NewReader(os.Stdin)
	for i = 0; i < lim-1; i++ {
		c, err := r.ReadByte()
		if rune(c) == '\n' || err != nil {
			break
		}
		s[i] = c
	}
	if rune(c) == '\n' {
		s[i] = c
		i++
	}
	return s, i
}
