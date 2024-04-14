package main

import "fmt"

func main() {
	var x []float64
	x = make([]float64, 5)
	fmt.Println(x)

	y := []float64{1, 2, 3}
	fmt.Println(y)
}
