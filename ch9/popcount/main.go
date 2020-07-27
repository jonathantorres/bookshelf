package main

// Exercise 9.2

import (
	"fmt"
	"sync"
)

// pc[i] is the population count of i
var pc [256]byte
var lookupOnce sync.Once

func main() {
	fmt.Println(PopCount(100))
}

func init() {
	lookupOnce.Do(loadLookup)
}

func loadLookup() {
	for i := range pc {
		pc[i] = pc[i/2] + byte(i&1)
	}
}

// PopCount returns the population count (number of set bits) of x
func PopCount(x uint64) int {
	return int(pc[byte(x>>(0*8))] +
		pc[byte(x>>(1*8))] +
		pc[byte(x>>(2*8))] +
		pc[byte(x>>(3*8))] +
		pc[byte(x>>(4*8))] +
		pc[byte(x>>(5*8))] +
		pc[byte(x>>(6*8))] +
		pc[byte(x>>(7*8))])
}
