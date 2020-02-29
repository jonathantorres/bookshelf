package main

import (
	"fmt"
)

// creating the "average" function
// that takes a slice of floats and
// returns the average
func main() {
	xs := []float64{
		98,
		93,
		77,
		82,
		83,
	}
	fmt.Println(average(xs))
}

func average(xs []float64) float64 {
	total := 0.0
	for _, v := range xs {
		total += v
	}
	return total / float64(len(xs))
}
