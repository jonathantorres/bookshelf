package main

import (
	"fmt"
	"github.com/jonathantorres/gointro/ch8/math"
)

func main() {
	x := []float64{
		11,22,33,
		89,39,45,
	}
	fmt.Println(math.Average(x))
	fmt.Println(math.Min(x))
	fmt.Println(math.Max(x))
}
