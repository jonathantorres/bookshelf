package main

import "fmt"

func main() {
	nums := []int{
		3,
		4,
		5,
		6,
	}
	fmt.Println(add(1, 2, 3, 4, 5))
	fmt.Println(add(nums...))
}

func add(nums ...int) int {
	var total int = 0
	for _, num := range nums {
		total += num
	}
	return total
}
