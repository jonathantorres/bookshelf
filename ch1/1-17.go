package main

import (
	"bufio"
	"fmt"
	"os"
)

const maxLine = 1000

func main() {
	var len int
	var max = 80
	line := make([]byte, maxLine)

	for {
		len = getLine(line, maxLine)
		if len == 0 {
			break
		}
		if len > max {
			fmt.Printf("%s\n", string(line))
		}
	}
}

func getLine(s []byte, lim int) int {
	var c byte
	var i int
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
	}
	return i
}
