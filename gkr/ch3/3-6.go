package main

import (
	"fmt"
	"math"
)

const maxLen = 25

func main() {
	s1 := make([]byte, maxLen)
	n1 := 10
	s2 := make([]byte, maxLen)
	n2 := 955
	s3 := make([]byte, maxLen)
	n3 := math.MinInt64

	itoa(n1, s1, 10)
	itoa(n2, s2, 5)
	itoa(n3, s3, 8)
	fmt.Printf("itoa(%d) = %s\n", n1, string(s1))
	fmt.Printf("itoa(%d) = %s\n", n2, string(s2))
	fmt.Printf("itoa(%d) = %s\n", n3, string(s3))
}

func itoa(n int, s []byte, w int) {
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
	if w > i {
		for ; i < w; i++ {
			s[i] = byte('0')
		}
	}
	if sign < 0 {
		s[i] = byte('-')
		i++
	}
	reverse(s, i)
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
