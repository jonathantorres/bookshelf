package main

import "fmt"

func main() {
	s := "JonaTHan"
	fmt.Printf("%s\n", s)
	for i := 0; i < 8; i++ {
		fmt.Printf("%c", lower(rune(s[i])))
	}
	fmt.Println()
}

func lower(c rune) rune {
	if c >= 'A' && c <= 'Z' {
		return c + 'a' - 'A'
	}
	return c
}
