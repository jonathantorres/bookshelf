package main

import (
	"fmt"
)

func main() {
	// creates the x array and adds 5 floating point numbers to it
	var x [5]float64
	x[0] = 98
	x[1] = 93
	x[2] = 77
	x[3] = 82
	x[4] = 83

	var total float64 = 0

	// loop through the array and add each value to "total"
	for i := 0; i < len(x); i++ {
		total += x[i]
	}

	// cast the len(x) value to a float
	fmt.Println(total / float64(len(x)))
}
