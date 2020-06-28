package main

// Exercise 4.1

import (
	"crypto/sha256"
	"fmt"
)

func main() {
	r := sha256.Sum256([]byte("Jonathan"))
	s := sha256.Sum256([]byte("Torres"))
	fmt.Printf("%x\n", r)
	fmt.Printf("%x\n", s)
	fmt.Println(bitDiff(r[:], s[:]))
}

func popCount(b byte) int {
	count := 0
	for ; b != 0; count++ {
		b &= b - 1
	}
	return count
}

func bitDiff(a, b []byte) int {
	count := 0
	for i := 0; i < len(a) || i < len(b); i++ {
		switch {
		case i >= len(a):
			count += popCount(b[i])
		case i >= len(b):
			count += popCount(a[i])
		default:
			count += popCount(a[i] ^ b[i])
		}
	}
	return count
}
