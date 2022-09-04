package main

import (
	"fmt"
	"strings"
)

func main() {
	fmt.Printf("%t\n", isupper1('G'))
	fmt.Printf("%t\n", isupper1('t'))
	fmt.Printf("%t\n", isupper2('K'))
	fmt.Printf("%t\n", isupper2('m'))
}

func isupper1(c rune) bool {
	return c >= 'A' && c <= 'Z'
}

func isupper2(c rune) bool {
	s := "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	return strings.ContainsRune(s, c)
}
