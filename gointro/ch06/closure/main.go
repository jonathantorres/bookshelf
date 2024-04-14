package main

import (
	"fmt"
)

func main() {
	add := func(x, y int) int {
		return x + y
	}
	fmt.Println(add(5, 5))

	x := 0
	increment := func() int {
		x++
		return x
	}
	fmt.Println(increment())
	fmt.Println(increment())
}
