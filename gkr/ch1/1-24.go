package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	for {
		line, err := r.ReadBytes(byte('\n'))
		if err != nil {
			if err != io.EOF {
				fmt.Printf("error: %s\n", err)
			}
			break
		}
		l := len(line)
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
