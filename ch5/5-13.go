package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"unicode"
)

const (
	maxLines = 5000
	pLines   = 10
	maxLen   = 1000
)

var lineptr [][]byte

func main() {
	var nlines int
	lineptr = make([][]byte, maxLines)
	switch len(os.Args) {
	case 1:
		nlines = pLines
		break
	case 2:
		nlines = process_input(os.Args)
		if nlines == -1 {
			fmt.Printf("Invalid format for optional argument -n\n")
			return
		}
		break
	default:
		fmt.Printf("Too many arguments!\n")
		return
	}

	n := readlines(lineptr, maxLines)
	if n >= 0 {
		writelines(lineptr)
	} else {
		fmt.Printf("error: input too big\n")
	}
}

func process_input(v []string) int {
	n := []byte(v[1])
	var c byte
	if rune(n[0]) != '-' {
		return -1
	} else {
		for _, r := range n {
			c = byte(r)
			if !unicode.IsDigit(rune(c)) {
				break
			}
		}
		r, err := strconv.Atoi(string(n))
		if err != nil {
			return -1
		}
		return r
	}
}

func readlines(lineptr [][]byte, maxlines int) int {
	var nlines int
	p := make([]byte, maxLen)
	for {
		l, n := getLine(maxLen)
		if n <= 0 {
			break
		}
		if nlines >= maxlines {
			return -1
		} else {
			copy(p, l)
			lineptr[nlines] = p
			nlines++
		}
	}
	return nlines
}

func writelines(lineptr [][]byte) {
	fmt.Printf("\n")
	for _, l := range lineptr {
		fmt.Printf("%s\n", string(l))
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
