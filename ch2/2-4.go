package main

import "fmt"

func main() {
	name := "Jonathan"
	fmt.Printf("%s\n", name)
	name = squeeze([]byte(name), "Ja")
	fmt.Printf("%s\n", name)
}

func squeeze(s1 []byte, s2 string) string {
	var i, j, k int
	for i, k = 0, 0; i < len(s1)-1; i++ {
		var inS2 bool
		for j = 0; j < len(s2)-1; j++ {
			if rune(s1[i]) == rune(s2[j]) {
				inS2 = true
				break
			}
		}
		if !inS2 {
			s1[k] = s1[i]
			k++
		}
	}
	return string(s1)
}
