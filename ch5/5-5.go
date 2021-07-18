package main

import "fmt"

func main() {
	s1 := []byte("john")
	s2 := []byte("johnny")
	s3 := make([]byte, 20)

	fmt.Printf("%d\n", strn_cmp(s1, s2, 2))
	fmt.Printf("%s\n", string(strn_cpy(s3, s1, 20)))
	fmt.Printf("%s\n", string(strn_cat(s3, s2, 20)))
}

func strn_cpy(d []byte, s []byte, n int) []byte {
	var i int
	var r []byte
	r = d
	for i = 0; i < n && i < len(s); i++ {
		d[i] = s[i]
	}
	return r
}

func strn_cat(d []byte, s []byte, n int) []byte {
	var r []byte
	var i, j int
	r = d
	for j = 0; d[j] != 0; j++ {
		// nothing
	}
	for i = 0; i < len(s) && i < n; i, j = i+1, j+1 {
		d[j] = s[i]
	}
	return r
}

func strn_cmp(s []byte, t []byte, n int) int {
	var i int
	for i = 0; i < n && (s[i] == t[i]); i++ {
		// nothing
	}
	if i == n {
		return 0
	} else {
		if s[i-1] > t[i-1] {
			return 1
		} else {
			return -1
		}
	}
}
