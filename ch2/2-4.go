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
	for i, k = 0, 0; i < len(s1); i++ {
		var in bool
		for j = 0; j < len(s2); j++ {
			if rune(s1[i]) == rune(s2[j]) {
				in = true
				break
			}
		}
		if !in {
			s1[k] = s1[i]
			k++
		}
	}
	if len(s2) > 0 {
		s1 = s1[:(len(s1)-len(s2))-1]
	}
	return string(s1)
}
