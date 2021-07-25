package main

import (
	"bufio"
	"fmt"
	"os"
)

const tabLen = 4
const maxLine = 1000

func main() {
	var ts rune = '\t'
	if len(os.Args) > 1 {
		ts = rune(os.Args[1][0])
	}

	for {
		l, n := getLine(maxLine)
		if n <= 0 {
			break
		}
		entab(l, n, ts)
		detab(l, n, ts)
		fmt.Printf("%s\n", l)
	}
}

func entab(s []byte, l int, ts rune) {
	var tabAdded bool
	for i := 0; i < l; i++ {
		if rune(s[i]) == ' ' && rune(s[i+1]) == ' ' && rune(s[i+2]) == ' ' && rune(s[i+3]) == ' ' {
			fmt.Printf("%c", ts)
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

func detab(s []byte, l int, ts rune) {
	for i := 0; i < l; i++ {
		if rune(s[i]) == ts {
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
