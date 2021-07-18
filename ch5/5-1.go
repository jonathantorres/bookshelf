package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"unicode"
)

const (
	MaxLen   = 1000
	BuffSize = 100
)

var buf []byte
var bufp int

func main() {
	buf = make([]byte, BuffSize)
	var n, r int
	r = getint(&n)
	if r > 0 {
		fmt.Printf("%d\n", n)
	} else if r == 0 {
		fmt.Printf("not a number\n")
	} else if r == -1 {
		fmt.Printf("end of file\n")
	} else {
		fmt.Printf("unknown error\n")
	}
}

func getint(n *int) int {
	var c byte
	var err error
	var sign int
	for {
		c, err = getch()
		if err != nil {
			return -1
		}
		if !unicode.IsSpace(rune(c)) {
			break
		}
	}
	if !unicode.IsDigit(rune(c)) && rune(c) != '+' && rune(c) != '-' && err != io.EOF {
		ungetch(c)
	}
	if rune(c) == '-' {
		sign = -1
	} else {
		sign = 1
	}
	if rune(c) == '+' || rune(c) == '-' {
		c, err = getch()
	}
	for *n = 0; unicode.IsDigit(rune(c)); c, err = getch() {
		*n = 10*(*n) + int((rune(c) - '0'))
	}
	*n *= sign
	if err != io.EOF {
		ungetch(c)
	}
	return int(c)
}

func getch() (byte, error) {
	if bufp > 0 {
		bufp--
		v := buf[bufp]
		return v, nil
	}
	r := bufio.NewReader(os.Stdin)
	return r.ReadByte()
}

func ungetch(c byte) {
	if bufp >= BuffSize {
		fmt.Printf("ungetch: too many characters\n")
	} else {
		buf[bufp] = c
		bufp++
	}
}
