package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

const (
	MaxLine    = 1000
	PatternLen = 100
)

func main() {
	var f *os.File
	var lineno int
	var c rune
	var except, number, pat_found bool
	var pattern, filename string
	var err error

	for i := 1; i < len(os.Args); i++ {
		if os.Args[i][0] == '-' {
			c = rune(os.Args[i][1])
			switch c {
			case 'x':
				except = true
				break
			case 'n':
				number = true
				break
			default:
				fmt.Printf("find: illegal option %c\n", c)
				os.Exit(1)
				break
			}
		} else {
			if !pat_found {
				pattern = os.Args[i]
				pat_found = true
			} else {
				filename = os.Args[i]
			}
		}
	}
	f, err = os.Open(filename)
	if err != nil {
		fmt.Printf("find: %s\n", err)
		os.Exit(1)
	}
	s := bufio.NewScanner(f)
	for s.Scan() {
		l := s.Text()
		if except {
			// do something
		}
		if strings.Contains(l, pattern) {
			if number {
				lineno++
				fmt.Printf("%d:", lineno)
			}
			fmt.Printf("%s\n", l)
		}
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
