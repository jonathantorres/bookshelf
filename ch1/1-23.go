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
		var ignore bool
		for i := 0; i < l; i++ {
			if rune(line[i]) == '/' && i+1 < l && rune(line[i+1]) == '/' {
				ignore = true
			}
			if !ignore {
				fmt.Printf("%c", rune(line[i]))
			}
		}
		if ignore {
			fmt.Printf("\n")
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
