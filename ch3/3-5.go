package main

import (
	"fmt"
	"math"
)

func main() {
	s1 := make([]byte, 100)
	s2 := make([]byte, 100)
	n := 530

	itob(n, s1, 16) // hex
	fmt.Printf("%d = %s\n", n, s1)
	itob(n, s2, 2) // base 2
	fmt.Printf("%d = %s\n", n, s2)
}

func itob(n int, s []byte, b int) {
	var i, sign, num int
	sign = n
	if sign < 0 {
		if n <= math.MinInt64 {
			n++
		}
		n = -n
	}
	for {
		num = n % b
		if num < 10 {
			s[i] = byte(num + '0')
			i++
		} else {
			s[i] = byte(num - 10 + 'a')
			i++
		}
		n = n / b
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

func reverse(s []byte, l int) {
	var i, j int
	var c byte
	for j = l - 1; i < j; i, j = i+1, j-1 {
		c = s[i]
		s[i] = s[j]
		s[j] = c
	}
}
