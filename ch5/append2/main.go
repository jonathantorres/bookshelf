package main

import "fmt"

func main() {
	var x[]float64
	x = make([]float64, 5, 10)
	x[0] = 3
	x = append(x, 45)
	y := append(x, 11)
	fmt.Println(x)
	fmt.Println(y)
}
