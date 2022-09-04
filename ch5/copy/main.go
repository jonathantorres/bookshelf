package main

import "fmt"

func main() {
	x := make([]float64, 5)
	y := []float64{1,2,3}
	fmt.Println(x)
	copy(x, y)
	fmt.Println(x)
	fmt.Println(y)
}
