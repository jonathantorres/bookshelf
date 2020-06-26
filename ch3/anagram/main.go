package main

// Exercise 3.12

import (
	"fmt"
	"strings"
	"bytes"
)

func main() {
	fmt.Println(isanagram("Hola", "Halo"))
	fmt.Println(isanagram("John", "Ohnn"))
	fmt.Println(isanagram("The eyes", "They see"))
}

func isanagram(s1, s2 string) bool {
	s1 = strings.ToLower(s1)
	s2 = strings.ToLower(s2)
	if len(s1) != len(s2) {
		return false
	}
	sb := []byte(s2)
	for _, let := range s1 {
		if j := bytes.IndexByte(sb, byte(let)); j != -1 {
			sb[j] = sb[len(sb)-1]
			sb = sb[:len(sb)-1]
		}
	}
	if len(sb) == 0 {
		return true
	}
	return false
}
