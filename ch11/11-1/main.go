package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"unicode"
	"unicode/utf8"
)

type Counts struct {
	un  map[rune]int
	utf [utf8.UTFMax + 1]int
	inv int
}

func main() {
	counts, err := charcount(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "charcount: %v\n", err)
		os.Exit(1)
	}
	fmt.Printf("rune\tcount\n")
	for c, n := range counts.un {
		fmt.Printf("%q\t%d\n", c, n)
	}
	fmt.Print("\nlen\tcount\n")
	for i, n := range counts.utf {
		if i > 0 {
			fmt.Printf("%d\t%d\n", i, n)
		}
	}
	if counts.inv > 0 {
		fmt.Printf("\n%d invalid UTF-8 characters\n", counts.inv)
	}
}

func charcount(input io.Reader) (*Counts, error) {
	counts := make(map[rune]int)    // counts of Unicode characters
	var utflen [utf8.UTFMax + 1]int // count of lengths of UTF-8 encodings
	var invalid int                 // count of invalid UTF-8 characters
	in := bufio.NewReader(input)
	for {
		r, n, err := in.ReadRune() // returns rune, nbytes, error
		if err == io.EOF {
			break
		}
		if err != nil {
			return nil, err
		}
		if r == unicode.ReplacementChar && n == 1 {
			invalid++
			continue
		}
		counts[r]++
		utflen[n]++
	}
	return &Counts{counts, utflen, invalid}, nil
}
