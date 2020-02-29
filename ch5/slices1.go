package main

import (
	"fmt"
)

func main() {
	// this is an empty slice
	var x []float64

	// creating a slice with 5 floating point numbers
	y := make([]float64, 5)

	// create a slice with 5 floating point numbers
	// but, this slice's array has a capacity of 10
	z := make([]float64, 5, 10)

	// another slice with a capacity of 8
	var w = make([]int64, 5, 8)
	// let's append 4 more values to it
	w = append(w, 1, 1, 1, 1)

	// another way to create a slice,
	// using the [low:high] expression
	foo := [5]float64{1, 2, 3, 4, 5}
	parts := foo[0:3]

	fmt.Println(x)
	fmt.Println(y)
	fmt.Println(z)
	fmt.Println(w)
	fmt.Println(parts)
}
