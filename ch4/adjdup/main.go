package main

// Exercise 4.5

import (
	"fmt"
)

func main() {
	s := []string{
		"a","b","b","c","c","d","e","e",
	}
	fmt.Println(s)
	s = remdup(s)
	fmt.Println(s)
}

func remdup(list []string) []string {
	res := make([]string, 0)
	for _, s := range list {
		in := false
		for _, s2 := range res {
			if s == s2 {
				in = true;
				break
			}
		}
		if !in {
			res = append(res, s)
		}
	}
	return res
}
