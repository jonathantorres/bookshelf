package main

import "fmt"

func main() {
	var x []float64 = make([]float64, 5)
	x[0] = 98
	x[1] = 93
	x[2] = 77
	x[3] = 82
	x[4] = 83
	fmt.Println(average(x))
}

func average(x []float64) float64 {
	var total float64 = 0
	for _, value := range x {
		total += value
	}
	return total / float64(len(x))
}
