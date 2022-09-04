package main

import "fmt"

func main() {
	s1 := "-a-zA-Z0-9-"
	s2 := make([]byte, 1000)

	expand([]byte(s1), s2)
	fmt.Printf("%s\n", string(s2))
}

func expand(s1 []byte, s2 []byte) {
	var trai bool
	var l int
	for _ = range s1 {
		l++
	}
	if rune(s1[l-1]) == '-' {
		trai = true
	}
	var k, i int
	if rune(s1[0]) == '-' {
		s2[k] = '-'
		k++
		i++
	}
	for {
		if i == len(s1)-1 {
			break
		}
		if rune(s1[i]) == '-' {
			for j := rune(s1[i-1]); j <= rune(s1[i+1]); j, k = j+1, k+1 {
				s2[k] = byte(j)
			}
		}
		i++
	}
	if trai {
		s2[k] = '-'
		k++
	}
}
