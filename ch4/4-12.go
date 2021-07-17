package main

import "fmt"

var i int

func main() {
	n := 324
	s := make([]byte, 25)

	itoa(n, s)
	fmt.Printf("%d = %s\n", n, string(s))
}

func itoa(n int, s []byte) {
	if n < 0 {
		s[i] = '-'
		i++
		n = -n
	}
	if (n / 10) > 0 {
		itoa(int(n/10), s)
	}
	s[i] = byte((n % 10) + '0')
	i++
}
