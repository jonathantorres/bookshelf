package main

// Exercise 5.15

import (
	"fmt"
)

func main() {
	fmt.Println(sum(1, 2, 3))
	fmt.Println(min(1, 2, 3))
	fmt.Println(min(6))
	fmt.Println(max(1, 2, 3))
	fmt.Println(max(6))
}

func sum(nums ...int) int {
	total := 0
	for _, n := range nums {
		total += n
	}
	return total
}

func min(num int, nums ...int) int {
	min := num
	for _, n := range nums {
		if n < min {
			min = n
		}
	}
	return min
}

func max(num int, nums ...int) int {
	max := num
	for _, n := range nums {
		if n > max {
			max = n
		}
	}
	return max
}
