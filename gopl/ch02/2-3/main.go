package main

import (
	"fmt"

	"github.com/jonathantorres/gopl/ch2/2-3/pcloop"
	"github.com/jonathantorres/gopl/ch2/2-3/popcount"
)

func main() {
	fmt.Println(popcount.PopCount(500))
	fmt.Println(pcloop.PopCount(500))
}
