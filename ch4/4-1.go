package main

import "fmt"

func main() {
	msg := "banana"
	sub := "na"
	fmt.Printf("%d\n", strrindex([]byte(msg), []byte(sub)))
}

func strrindex(s []byte, t []byte) int {
	slen := len(s)
	tlen := len(t)

	reverse(s, slen)
	reverse(t, tlen)
	i := strindex(s, t)
	if i >= 0 {
		i = (slen - tlen) - i
	}
	reverse(s, slen)
	reverse(t, tlen)
	return i
}

func strindex(s []byte, t []byte) int {
	var i, j, k int
	for i = 0; i < len(s); i++ {
		for j = i; k < len(t) && s[j] == t[k]; j, k = j+1, k+1 {
			// do nothing
		}
		if k > 0 && k == len(t) {
			return i
		}
	}
	return -1
}

func reverse(s []byte, l int) {
	var i, j int
	var c byte
	for j = l - 1; i < j; i, j = i+1, j-1 {
		c = s[i]
		s[i] = s[j]
		s[j] = c
	}
}
