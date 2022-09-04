package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	var blanks int
	var tabs int
	var newlines int
	for {
		b, err := r.ReadByte()
		if err != nil {
			break
		}
		if rune(b) == ' ' {
			blanks++
		} else if rune(b) == '\t' {
			tabs++
		} else if rune(b) == '\n' {
			newlines++
		}
	}
	fmt.Printf("\nb:%d,t:%d,n:%d\n", blanks, tabs, newlines)
}
