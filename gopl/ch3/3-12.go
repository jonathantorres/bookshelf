package main

import (
	"fmt"
	"strings"
)

func main() {
	fmt.Println(anagram("Debit card", "Bad credit"))
	fmt.Println(anagram("Dormitory", "Dirty room"))
	fmt.Println(anagram("School master", "The classroom"))
	fmt.Println(anagram("Jonathan", "Thiselse"))
}

func anagram(s1, s2 string) bool {
	ns1, ns2 := strings.ToLower(s1), strings.ToLower(s2)
	ns1 = strings.ReplaceAll(ns1, " ", "")
	ns2 = strings.ReplaceAll(ns2, " ", "")

	if len(ns1) != len(ns2) {
		return false
	}
	for _, c := range ns1 {
		if strings.IndexRune(ns2, c) != -1 {
			ns2 = strings.Replace(ns2, string(c), "", 1)
		}
	}
	if ns2 == "" {
		return true
	}
	return false
}
