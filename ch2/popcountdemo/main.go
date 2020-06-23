package main

import (
	"fmt"
	"github.com/jonathantorres/gopl/ch2/popcount"
)

func main() {
	fmt.Println(popcount.PopCount(100))
	fmt.Println(popcount.PopCountShift(100))
	fmt.Println(popcount.PopCountRight(100))
}
