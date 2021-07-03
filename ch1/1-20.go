package main

import (
	"bufio"
	"fmt"
	"os"
)

const maxLine = 1000
const tabLen = 4

func main() {
	for {
		line, l := getLine(maxLine)
		detab(line, l)
		fmt.Printf("%s\n", string(line))
	}
}

func detab(s []byte, l int) {
	for i := 0; i < l; i++ {
		if rune(s[i]) == '\t' {
			s[i] = byte(' ')
			for j := l - 1; j >= i+1; j-- {
				s[j+(tabLen-1)] = s[j]
			}
			for k := 1; k < tabLen; k++ {
				s[i+k] = byte(' ')
			}
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
