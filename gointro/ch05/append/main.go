package main

import "fmt"

func main() {
	x := []float64{
		1,2,3,
	}
	fmt.Println(x)
	y := append(x, 1, 1)
	fmt.Println(y)
	fmt.Println(x)
}
