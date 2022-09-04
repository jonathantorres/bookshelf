package main

import "fmt"

func main() {
	s1 := "Jonathan"
	s2 := "ona"
	s3 := "bum"

	fmt.Printf("%s in %s = %d\n", s1, s2, any(s1, s2)) // 1
	fmt.Printf("%s in %s = %d\n", s1, s3, any(s1, s3)) // -1
}

func any(s1 string, s2 string) int {
	idx := -1
	for i := range s1 {
		var found bool
		for j := range s2 {
			if rune(s1[i]) == rune(s2[j]) {
				idx = i
				found = true
				break
			}
		}
		if found {
			break
		}
	}
	return idx
}
