package main

import (
	"bufio"
	"fmt"
	"os"
)

const maxLine = 1000

func main() {
	var i int
	s := make([]byte, maxLine)
	r := bufio.NewReader(os.Stdin)
	for {
		b, err := r.ReadByte()
		if err != nil {
			break
		}
		c := rune(b)
		if c != '\n' {
			if i < maxLine {
				s[i] = b
				i++
			}
		} else {
			fmt.Printf("%s\n", string(s))
			i = 0
		}
	}
}
