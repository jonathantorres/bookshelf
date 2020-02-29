package main

import (
	"fmt"
)

func main() {
	// this creates an array that will hold five integers
	var x [5]int

	// assigns the 100 value to the fifth element on the array
	x[4] = 100

	fmt.Println(x)
}
