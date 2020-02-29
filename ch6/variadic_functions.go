package main

import "fmt"

// The "add" function can take
// any number of parameters
func main() {
	fmt.Println(add(1, 2, 3, 4, 5))

	// it can also map the values of a slice using the ellipsis
	nums := []int{
		3,
		4,
		5,
		6,
	}
	fmt.Println(add(nums...))
}

func add(args ...int) int {
	total := 0

	for _, v := range args {
		total += v
	}

	return total
}
