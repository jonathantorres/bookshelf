package main

import "fmt"

var i int
var k int = 1

func main() {
	s := []byte("Jonathan Torres")
	fmt.Printf("%s\n", string(s))
	reverse(s)
	fmt.Printf("%s\n", string(s))
}

func reverse(s []byte) {
	var c byte
	j := len(s) - k
	if i < j {
		c = s[i]
		s[i] = s[j]
		i++
		s[j] = c
		k++
		reverse(s)
	}
}
