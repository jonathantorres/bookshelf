package main

import (
	"crypto/sha256"
	"fmt"

	"github.com/jonathantorres/gopl/ch2/2-3/popcount"
)

func main() {
	sha1 := sha256.Sum256([]byte("Jonathan"))
	sha2 := sha256.Sum256([]byte("Torres"))

	fmt.Printf("%x\n", sha1)
	fmt.Printf("%x\n", sha2)
	fmt.Printf("%d\n", bitDiff(&sha1, &sha2))
}

func bitDiff(sha1, sha2 *[sha256.Size]byte) int {
	r := 0
	for i := 0; i < sha256.Size; i++ {
		b1 := uint8(sha1[i])
		b2 := uint8(sha2[i])
		r += popcount.PopCount(uint64(b1 ^ b2))
	}
	return r
}
