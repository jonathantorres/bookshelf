package main

import (
	"fmt"
	"unicode"
)

func main() {
	s1 := []byte("Jonathan    Torres")
	s2 := []byte("Jonathan    OF    Torres")
	s3 := []byte("Jonathan    THE   AND   Torres")
	fmt.Println(string(remSpace(s1)))
	fmt.Println(string(remSpace(s2)))
	fmt.Println(string(remSpace(s3)))
}

func remSpace(s []byte) []byte {
	i := 0
sloop:
	for _, v := range string(s) {
		for {
			if !unicode.IsSpace(v) || i+1 > len(s)-1 {
				break
			}
			if unicode.IsSpace(rune(s[i+1])) {
				copy(s[i:], s[i+1:])
				s = s[:len(s)-1]
				continue sloop
			}
			break
		}
		i++
	}
	return s
}
