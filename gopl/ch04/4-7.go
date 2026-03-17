package main

import (
	"fmt"
	"unicode/utf8"
)

func main() {
	s1 := reverse([]byte("Jonathan Torres"))
	fmt.Println(string(s1))
	s2 := reverse([]byte("gülümsemek"))
	fmt.Println(string(s2))
	s3 := reverse([]byte("aşk"))
	fmt.Println(string(s3))
	s4 := reverse([]byte("köpek"))
	fmt.Println(string(s4))
}

func reverse(s []byte) []byte {
	r := make([]byte, len(s))
	for i := len(s) - 1; i >= 0; i-- {
		rl := utf8.RuneLen(rune(s[i]))
		if rl > 1 && i > 0 {
			if utf8.RuneStart(s[i]) {
				r = append(r, s[i:i+rl]...)
			}
		} else {
			r = append(r, s[i])
		}
	}
	return r
}
