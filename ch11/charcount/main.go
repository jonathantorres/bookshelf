package main

// Exercise 11.1

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"unicode"
	"unicode/utf8"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	counts, utflen, invalid, err := charcount(in)
	if err != nil {
		fmt.Fprintf(os.Stderr, "charcount: %v\n", err)
		os.Exit(1)
	}
	fmt.Printf("type\tcount\n")
	for c, n := range counts {
		fmt.Printf("%s\t%d\n", c, n)
	}
	fmt.Print("\nlen\tcount\n")
	for i, n := range utflen {
		if i > 0 {
			fmt.Printf("%d\t%d\n", i, n)
		}
	}
	if invalid > 0 {
		fmt.Printf("\n%d invalid UTF-8 characters\n", invalid)
	}
}

func charcount(in *bufio.Reader) (map[string]int, [utf8.UTFMax + 1]int, int, error) {
	counts := make(map[string]int)
	var utflen [utf8.UTFMax + 1]int
	invalid := 0
	for {
		r, n, err := in.ReadRune()
		if err == io.EOF {
			break
		}
		if err != nil {
			return nil, utflen, 0, err
		}
		if r == unicode.ReplacementChar && n == 1 {
			invalid++
			continue
		}
		switch {
		case unicode.IsLetter(r):
			counts["letters"]++
		case unicode.IsDigit(r):
			counts["numbers"]++
		case unicode.IsSpace(r):
			counts["space"]++
		case unicode.IsSymbol(r):
			counts["symbol"]++
		default:
			counts["untracked"]++
		}
		utflen[n]++
	}
	return counts, utflen, invalid, nil
}
