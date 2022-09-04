package main

import (
	"fmt"

	"github.com/jonathantorres/gopl/ch2/2-5/pcright"
	"github.com/jonathantorres/gopl/ch2/2-5/popcount"
)

func main() {
	fmt.Println(popcount.PopCount(500))
	fmt.Println(pcright.PopCount(500))
}
