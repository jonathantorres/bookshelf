package main

import (
	"fmt"
)

func main() {
	nums := []int{
		10,
		10,
		10,
	}
	fmt.Println(sum(nums))
}

func sum(nums []int) int {
	total := 0
	for _, v := range nums {
		total += v
	}
	return total
}
