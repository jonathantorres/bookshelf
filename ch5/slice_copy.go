package main

import (
	"fmt"
)

func main() {
	// create a slice with 3 integers
	slice1 := []int{1, 2, 3}

	// create a slice that can hold 2 integer values
	slice2 := make([]int, 2)

	// copies the contents of slice1 into slice2
	// since slice2 can hold only 2 numbers, only
	// the first 2 values of slice1 are copied
	copy(slice2, slice1)

	fmt.Println(slice2, slice1)
}
