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
		entab(line, l)
	}
}

func entab(s []byte, l int) {
	var tabAdded bool
	for i := 0; i < l; i++ {
		if rune(s[i]) == ' ' && rune(s[i+1]) == ' ' && rune(s[i+2]) == ' ' && rune(s[i+3]) == ' ' {
			fmt.Printf("\t")
			tabAdded = true
		} else if rune(s[i]) == ' ' {
			if !tabAdded {
				fmt.Printf("%c", rune(s[i]))
			}
		} else {
			tabAdded = false
			fmt.Printf("%c", rune(s[i]))
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
