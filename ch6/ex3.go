package main

import (
	"fmt"
)

func main() {
	nums := []float64{
		55, 67, 89, 90,
		67, 12, 11, 97,
		69, 45, 22, 96,
	}
	fmt.Println(bigger(nums...))
}

func bigger(nums ...float64) float64 {
	var bigger float64
	for i, num := range nums {
		if i == 0 || num > bigger {
			bigger = num
		}
	}
	return bigger
}
