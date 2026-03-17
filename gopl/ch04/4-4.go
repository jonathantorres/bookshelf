package main

import (
	"fmt"
)

func main() {
	n := []int{
		1, 2, 3, 4, 5,
	}
	fmt.Println(n)
	n = rotate(n, 2, true)
	// n = rotate(n, 3, false)
	fmt.Println(n)
}

func rotate(s []int, amt int, left bool) []int {
	if amt > len(s) {
		panic("rotation amount cannot be bigger than slice length")
	}
	f := make([]int, 0, len(s))
	if left {
		l := s[:amt]
		r := s[amt:]
		f = append(f, r...)
		f = append(f, l...)
	} else {
		l := s[len(s)-amt:]
		r := s[:len(s)-amt]
		f = append(f, l...)
		f = append(f, r...)
	}
	return f
}

func rot(s []int, amt int, left bool) {
	if !left {
		reverse(s)
	}
	reverse(s[:amt])
	reverse(s[amt:])
	if left {
		reverse(s)
	}
}

func reverse(s []int) {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
}
