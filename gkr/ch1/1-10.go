package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	for {
		b, err := r.ReadByte()
		if err != nil {
			break
		}
		c := rune(b)
		if c == '\t' {
			fmt.Printf("\\t")
		} else if c == '\b' {
			fmt.Printf("\\b")
		} else if c == '\\' {
			fmt.Printf("\\\\")
		} else {
			fmt.Printf("%c", c)
		}
	}
}
