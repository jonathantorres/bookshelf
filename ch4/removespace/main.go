package main

// Exercise 4.6

import (
	"fmt"
	"unicode"
)

func main() {
	s := []byte{
		'a','d',' ','_','r','s','q','a','d',
	}
	fmt.Printf("%q\n", s)
	s = removespaces(s)
	fmt.Printf("%q\n", s)
}

func removespaces(s []byte) []byte {
	res := []byte{}
	for _, r := range s {
		if !unicode.IsSpace(rune(r)) {
			res = append(res, r)
		}
	}
	return res
}
