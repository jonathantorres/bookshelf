package main

import "fmt"

func main() {
	name := make([]byte, 0, 100)
	name = append(name, []byte("Jonathan ")...)
	lastName := []byte("Torres")
	p_strcat(&name, &lastName)
	fmt.Printf("%s\n", string(name))
}

func p_strcat(s *[]byte, t *[]byte) {
	var i int
	// find the end of s
	for {
		if i >= len(*s)-1 {
			break
		}
		i++
	}
	for _, x := range *t {
		*s = append(*s, x)
	}
}
