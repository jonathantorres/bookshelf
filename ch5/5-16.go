package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strconv"
)

const (
	maxLines = 5000
	maxLen   = 1000
)

var lineptr [][]byte

func main() {
	lineptr = make([][]byte, maxLines)
	nlines := 0
	var numeric bool
	var reversed bool
	var fold bool
	var dir bool
	if len(os.Args) > 1 {
		for _, s := range os.Args {
			if s == "-n" {
				numeric = true
			}
			if s == "-r" {
				reversed = true
			}
			if s == "-f" {
				fold = true
			}
			if s == "-d" {
				dir = true
			}
		}
	}
	nlines = readlines(lineptr, maxLines)
	if nlines >= 0 {
		var cmpfunc func(s1, s2 []byte, dir bool) int
		if numeric {
			cmpfunc = numcmp
		} else {
			cmpfunc = strcmp
		}
		qsort2(lineptr, 0, nlines-1, cmpfunc, reversed, fold, dir)
		writelines(lineptr)
	} else {
		fmt.Printf("input too big to sort\n")
	}
}

func qsort2(v [][]byte, left int, right int, comp func(s1, s2 []byte, dir bool) int, reversed bool, fold bool, dir bool) {
	var i, last int
	v1, v2 := make([]byte, 1000), make([]byte, 1000)
	if left >= right {
		return
	}
	swap(v, left, (left+right)/2)
	last = left
	for i = left + 1; i <= right; i++ {
		if fold {
			copy(v1, v[i])
			copy(v2, v[left])
			v1 = bytes.ToLower(v1)
			v2 = bytes.ToLower(v2)
		} else {
			copy(v1, v[i])
			copy(v2, v[left])
		}
		if !reversed {
			if comp(v[i], v[left], dir) < 0 {
				last++
				swap(v, last, i)
			} else {
				if comp(v[i], v[left], dir) > 0 {
					last++
					swap(v, last, i)
				}
			}
		}
	}
	swap(v, left, last)
	qsort2(v, left, last-1, comp, reversed, fold, dir)
	qsort2(v, last+1, right, comp, reversed, fold, dir)
}

func swap(v [][]byte, i int, j int) {
	var tmp []byte
	tmp = v[i]
	v[i] = v[j]
	v[j] = tmp
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

func numcmp(s1, s2 []byte, dir bool) int {
	var v1, v2 float64
	var err error
	if dir {
		// ignore on this case
	}
	v1, err = strconv.ParseFloat(string(s1), 64)
	if err != nil {
		return -1
	}
	v2, err = strconv.ParseFloat(string(s2), 64)
	if err != nil {
		return -1
	}
	if v1 < v2 {
		return -1
	} else if v1 > v2 {
		return 1
	} else {
		return 0
	}
}

func strcmp(s1, s2 []byte, dir bool) int {
	old := "!@#$%^&*()_"
	var v1 string
	var v2 string
	if dir {
		v1 = string(bytes.ReplaceAll(s1, []byte(old), []byte("")))
		v2 = string(bytes.ReplaceAll(s2, []byte(old), []byte("")))
	} else {
		v1 = string(s1)
		v2 = string(s2)
	}

	if v1 > v2 {
		return 1
	} else if v1 < v2 {
		return -1
	} else {
		return 0
	}
}
