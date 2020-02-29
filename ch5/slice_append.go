package main

import (
	"fmt"
)

func main() {
	// create a slice with three integers
	slice1 := []int{1, 2, 3}

	// use append to add the values 4 and 5 at the end of it
	slice2 := append(slice1, 4, 5)

	fmt.Println(slice1, slice2)
}
