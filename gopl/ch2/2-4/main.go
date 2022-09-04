package main

import (
	"fmt"

	"github.com/jonathantorres/gopl/ch2/2-4/pcshift"
	"github.com/jonathantorres/gopl/ch2/2-4/popcount"
)

func main() {
	fmt.Println(popcount.PopCount(500))
	fmt.Println(pcshift.PopCount(500))
}
