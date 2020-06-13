package main

import "fmt"

func main() {
	slice1 := make([]float64, 3, 5)
	slice1[0] = 1
	slice1[1] = 2
	slice1[2] = 3
	slice2 := append(slice1, 4, 5)
	fmt.Println(slice1)
	fmt.Println(slice2)
}
