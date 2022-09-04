package main

import (
	"fmt"
)

func main() {
	s := []string{
		"foo",
		"bar",
		"baz",
		"baz",
		"foo",
		"foo",
		"bar",
		"bar",
	}
	fmt.Println(s)
	s = removeAdj(s)
	fmt.Println(s)
}

func removeAdj(s []string) []string {
	for i := 0; i < len(s); i++ {
		if i+1 <= len(s)-1 && s[i] == s[i+1] {
			copy(s[i:], s[i+1:])
			s = s[:len(s)-1]
		}
	}
	return s
}
