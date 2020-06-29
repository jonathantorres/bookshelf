package main

import "fmt"

// Exercise 4.7

func main() {
	n := []byte{'J', 'o', 'n', 'a', 't', 'h', 'a', 'n'}
	fmt.Printf("%q\n", n)
	reverse(n)
	fmt.Printf("%q\n", n)
}

func reverse(s []byte) {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
}
