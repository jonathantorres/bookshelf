package main

import (
	"fmt"
)

func main() {
	// find the smallest number in this list
	x := []int{
		48, 96, 86, 68,
		57, 82, 63, 70,
		37, 34, 83, 27,
		19, 97, 9, 17,
	}

	var smallest int

	for i, num := range x {
		if i == 0 || num < smallest {
			smallest = num
		}
	}
	fmt.Println(smallest)
}
