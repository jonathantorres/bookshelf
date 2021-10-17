package main

import (
	"fmt"
	"math"
	"strings"
)

func main() {
	s1 := "0xFF00FF"
	s2 := "cc0033"
	s3 := "DEAD"

	fmt.Printf("%s = %d\n", s1, htoi(s1))
	fmt.Printf("%s = %d\n", s2, htoi(s2))
	fmt.Printf("%s = %d\n", s3, htoi(s3))
}

func getMap(c rune) int {
	m := "0123456789abcdef"
	var pos int
	for i := 0; i < len(m); i++ {
		if strings.ToLower(string(c)) == string(m[i]) {
			pos = i
			break
		}
	}
	return pos
}

func htoi(s string) int {
	var total int
	var prefix bool
	var i int
	if s[0] == '0' && (s[1] == 'x' || s[1] == 'X') {
		i = 2
		prefix = true
	}
	for j := len(s) - 1; i <= len(s)-1; i, j = i+1, j-1 {
		var amt int
		if prefix {
			amt = 2
		}
		total += getMap(rune(s[i])) * int(math.Pow(16.0, float64(j-amt)))
	}
	return total
}
