package main

import (
	"bufio"
	"fmt"
	"os"
)

const maxLine = 1000

func main() {
	line2 := make([]byte, maxLine)
	line3 := make([]byte, maxLine)

	for {
		line, l := getLine(maxLine)
		if l == 0 {
			break
		}
		escape(line2, line)
		rEscape(line3, line2)
		fmt.Printf("%s\n", string(line2))
		fmt.Printf("%s\n", string(line3))
	}
}

func escape(s []byte, t []byte) {
	for i, j := 0, 0; t[i] != 0; i, j = i+1, j+1 {
		switch rune(t[i]) {
		case '\n':
			s[j] = '\\'
			j++
			s[j] = 'n'
			break
		case '\t':
			s[j] = '\\'
			j++
			s[j] = 't'
			break
		default:
			s[j] = t[i]
			break
		}
	}
}

func rEscape(s []byte, t []byte) {
	for i, j := 0, 0; t[i] != 0; i, j = i+1, j+1 {
		switch rune(t[i]) {
		case '\\':
			if t[i+1] == 't' {
				s[j] = '\t'
				i++
			} else if t[i+1] == 'n' {
				s[j] = '\n'
				i++
			} else {
				s[j] = t[i]
			}
			break
		default:
			s[j] = t[i]
			break
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
