package main

import "fmt"

func biggest(nums ...int) int {
	var biggest int
	for i, num := range nums {
		if i == 0 || num > biggest {
			biggest = num
		}
	}
	return biggest
}

func main() {
	nums := []int{
		6,77,8,2,
		67,1,23,78,
	}
	fmt.Println(biggest(3,4,5,1,9))
	fmt.Println(biggest(nums...))
}
