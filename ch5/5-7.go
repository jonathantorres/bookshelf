package main

import (
	"bufio"
	"fmt"
	"os"
)

const MaxLen = 1000

func main() {
	var line []byte
	var l int
	for {
		line, l = getLine(MaxLen)
		if l <= 0 {
			break
		}
		fmt.Printf("%s\n", line)
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
