package main

import (
	"bufio"
	"fmt"
	"os"
)

const maxLine = 1000

func main() {
	rev := make([]byte, maxLine)
	for {
		line, l := getLine(maxLine)
		reverse(line, rev, l)
		fmt.Printf("%s\n", string(rev))
		reset(rev)
	}
}

func reverse(s []byte, rev []byte, lim int) {
	for i, j := lim-1, 0; i >= 0; i, j = i-1, j+1 {
		rev[j] = s[i]
	}
}

func reset(s []byte) {
	for i := range s {
		s[i] = 0
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
