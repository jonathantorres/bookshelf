package main

import "fmt"

func main() {
	s1 := []byte("first")
	s2 := []byte("rst")
	s3 := []byte("foo")
	fmt.Printf("%d\n", strend(s1, s2)) // 1
	fmt.Printf("%d\n", strend(s1, s3)) // 0
}

func strend(s []byte, t []byte) int {
	si, ti := len(s)-1, len(t)-1
	n := ti
	for {
		if n == 0 || s[si] != t[ti] {
			break
		}
		n--
		si--
		ti--
	}
	if n > 0 {
		return 0
	}
	return 1
}
