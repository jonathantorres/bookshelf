package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	if strings.Compare(os.Args[0], "lower") == 0 {
		for {
			b, err := r.ReadByte()
			if err != nil {
				break
			}
			fmt.Printf("%c", unicode.ToLower(rune(b)))
		}
	} else {
		for {
			b, err := r.ReadByte()
			if err != nil {
				break
			}
			fmt.Printf("%c", unicode.ToUpper(rune(b)))
		}
	}
}
