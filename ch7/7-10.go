package main

import (
	"fmt"
	"sort"
	"strings"
)

type str string

func (s str) Len() int {
	return len(string(s))
}

func (s str) Less(i, j int) bool {
	return s[i] < s[j]
}

func (s str) Swap(i, j int) {
	sli := []byte(s)
	sli[i], sli[j] = sli[j], sli[i]
}

func main() {
	s1 := str("madam")
	s2 := str("noon")
	s3 := str(strings.Replace("red rum sir is murder", " ", "", -1))
	fmt.Println(isPalindrome(s1))
	fmt.Println(isPalindrome(s2))
	fmt.Println(isPalindrome(s3))
}

func isPalindrome(s sort.Interface) bool {
	ispal := true
	for i, j := 0, s.Len()-1; i < j; i, j = i+1, j-1 {
		if !(!s.Less(i, j) && !s.Less(j, i)) {
			ispal = false
		}
	}
	return ispal
}
