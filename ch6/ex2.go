package main

import (
	"fmt"
)

func main() {
	x, y := half(1)
	z, w := half(2)

	fmt.Println(x, y)
	fmt.Println(z, w)
}

func half(x int) (int, bool) {
	half := x / 2
	isEven := false
	if x%2 == 0 {
		isEven = true
	}

	return half, isEven
}
