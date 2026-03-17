package main

import "fmt"

func main() {
	n := []int{4, 5, 2, 33, 7, 10, 50, 20}
	mx := max(n[0], n[1:]...)
	mi := min(n[0], n[1:]...)
	fmt.Println(mx)
	fmt.Println(mi)
}

func max(max int, nums ...int) int {
	for _, n := range nums {
		if n > max {
			max = n
		}
	}
	return max
}

func min(min int, nums ...int) int {
	for _, n := range nums {
		if n < min {
			min = n
		}
	}
	return min
}
