package main

import (
	"fmt"
)

func main() {
	// the add() function created inside the main() function
	add := func(x, y int) int {
		return x + y
	}
	fmt.Println(add(5, 5))

	// this increment() function has access to the x variable
	x := 0
	increment := func() int {
		x++
		return x
	}
	fmt.Println(increment())
	fmt.Println(increment())

	// calling the even number generator
	nextEven := makeEvenGenerator()
	fmt.Println(nextEven())
	fmt.Println(nextEven())
	fmt.Println(nextEven())
}

// this is a function that returns another function
func makeEvenGenerator() func() uint {
	i := uint(0)
	return func() (ret uint) {
		ret = i
		i += 2
		return
	}
}
