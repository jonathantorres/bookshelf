package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode"
)

const (
	MaxWord = 100
	BufSize = 100
)

var sp, bufp int
var buf []byte

type key struct {
	word  string
	count int
}

var keytab = []key{
	{"auto", 0},
	{"break", 0},
	{"case", 0},
	{"char", 0},
	{"continue", 0},
	{"unsigned", 0},
	{"void", 0},
	{"volatile", 0},
	{"while", 0},
}

func main() {
	buf = make([]byte, BufSize)
	word := make([]byte, MaxWord)
	nKeys := len(keytab)
	for {
		_, err := getword(word, MaxWord)
		if err != nil {
			break
		}
		if unicode.IsLetter(rune(word[0])) || unicode.IsDigit(rune(word[0])) {
			n := binsearch(string(word), keytab, nKeys)
			if n >= 0 {
				keytab[n].count++
			}
		}
	}
	for n := 0; n < nKeys; n++ {
		if keytab[n].count > 0 {
			fmt.Printf("%d %s\n", keytab[n].count, keytab[n].word)
		}
	}
}

func binsearch(word string, tab []key, n int) int {
	var low, high, mid int
	var cond int
	high = n - 1
	for {
		if low > high {
			break
		}
		mid = (low + high) / 2
		cond = strings.Compare(word, tab[mid].word)
		if cond < 0 {
			high = mid - 1
		} else if cond > 0 {
			low = mid + 1
		} else {
			return mid
		}
	}
	return -1
}

func getword(word []byte, lim int) (byte, error) {
	var c byte
	var err error
	for {
		c, err = getch()
		if err != nil {
			return byte(0), err
		}
		if !unicode.IsSpace(rune(c)) {
			break
		}
	}
	if !acceptable(rune(c)) {
		return c, nil
	}
	for i := 0; lim > 0; lim, i = lim-1, i-1 {
		c, err = getch()
		if err != nil {
			return byte(0), err
		}
		if !acceptable(rune(c)) {
			ungetch(c)
			break
		}
		word[i] = c
	}
	return word[0], nil
}

func acceptable(c rune) bool {
	if unicode.IsDigit(c) || unicode.IsLetter(c) || c == '_' || c == '"' || c == '#' || c == '/' {
		return true
	}
	return false
}

func getch() (byte, error) {
	if bufp > 0 {
		v := buf[bufp]
		bufp--
		return v, nil
	}
	r := bufio.NewReader(os.Stdin)
	return r.ReadByte()
}

func ungetch(c byte) {
	if bufp >= BufSize {
		fmt.Printf("ungetch: too many characters\n")
	} else {
		buf[bufp] = c
		bufp++
	}
}
