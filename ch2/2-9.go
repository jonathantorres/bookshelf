package main

import "fmt"

func main() {
	n := 75
	fmt.Printf("num of 1's in %d = %d\n", n, bitcount(n))
}

func bitcount(x int) int {
	var b int
	for b = 0; x != 0; x &= (x - 1) {
		if x > 0 {
			b++
		}
	}
	return b
}
