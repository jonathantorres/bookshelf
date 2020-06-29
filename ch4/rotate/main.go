package main

// Exercise 4.4

import (
	"fmt"
)

func main() {
	nums := []int{
		1, 2, 3, 4, 5,
	}
	fmt.Println(nums)
	nums = rotate(nums, 3)
	fmt.Println(nums)
}

func rotate(slice []int, amount int) []int {
	if amount == 0 || len(slice) == 0 || amount == len(slice) {
		return slice
	}
	res := make([]int, 0)
	res = append(res, slice[amount:]...)
	res = append(res, slice[:amount]...)
	return res
}
