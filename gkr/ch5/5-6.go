package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
)

func main() {
	lim := 100
	msg, _ := getLine(lim)
	reverse(msg, lim)
	fmt.Printf("%s\n", msg)

	n := make([]byte, 20)
	itoa(1800, n)
	fmt.Printf("%s\n", n)

	s1 := []byte("Jonathan")
	s2 := []byte("han")
	fmt.Printf("%d\n", strindex(s1, s2)) // expected 5
}

func strindex(s []byte, t []byte) int {
	var i, j, k int
	for i = 0; i < len(s); i++ {
		for j = i; k < len(t) && s[j] == t[k]; j, k = j+1, k+1 {
			// do nothing
		}
		if k > 0 && k == len(t) {
			return i
		}
	}
	return -1
}

func itoa(n int, s []byte) {
	var i, sign int
	sign = n
	if sign < 0 {
		if n <= math.MinInt64 {
			n++
		}
		n = -n
	}
	i = 0
	for {
		s[i] = byte(n%10 + '0')
		i++
		n = n / 10
		if n == 0 {
			break
		}
	}
	if sign < 0 {
		s[i] = byte('-')
		i++
	}
	reverse(s, i)
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

func reverse(s []byte, l int) {
	var i, j int
	var c byte
	for j = l - 1; i < j; i, j = i+1, j-1 {
		c = s[i]
		s[i] = s[j]
		s[j] = c
	}
}
