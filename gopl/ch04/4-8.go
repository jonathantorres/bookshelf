package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"unicode"
)

func main() {
	counts := make(map[string]int)
	invalid := 0 // count of invalid UTF-8 characters

	in := bufio.NewReader(os.Stdin)
	for {
		r, n, err := in.ReadRune() // returns rune, nbytes, error
		if err == io.EOF {
			break
		}
		if err != nil {
			fmt.Fprintf(os.Stderr, "charcount: %v\n", err)
			os.Exit(1)
		}
		if r == unicode.ReplacementChar && n == 1 {
			invalid++
			continue
		}
		if unicode.IsLetter(r) {
			counts["letter"]++
			if unicode.IsLower(r) {
				counts["lower"]++
			} else {
				counts["upper"]++
			}
		}
		if unicode.IsDigit(r) {
			counts["digits"]++
		}
		if unicode.IsControl(r) {
			counts["control"]++
		}
	}
	fmt.Printf("type\tcount\n")
	for t, c := range counts {
		fmt.Printf("%s\t%d\n", t, c)
	}
	if invalid > 0 {
		fmt.Printf("\n%d invalid UTF-8 characters\n", invalid)
	}
}
