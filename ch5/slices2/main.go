package main

import "fmt"

func main() {
	x := []float64{
		1,2,3,4,5,
	}
	fmt.Println(x[:])
	fmt.Println(x[2:4])
	fmt.Println(x[:4])
	fmt.Println(x[1:len(x)])
}
