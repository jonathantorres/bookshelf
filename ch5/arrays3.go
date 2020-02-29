package main

import (
	"fmt"
)

func main() {
	// creates the "x" array with 5 float numbers
	x := [5]float64{
		98,
		93,
		77,
		82,
		83,
	}

	var total float64 = 0

	// loops through the "x" array and adds the values to "total"
	// _ it's supposed to be index (i), but since we're not using it
	// we satisfy the compiler by using the underscore instead
	for _, value := range x {
		total += value
		// fmt.Println(i, value)
	}

	fmt.Println(total / float64(len(x)))
}
