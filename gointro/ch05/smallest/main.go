package main

import "fmt"

func main() {
	x := []int{
		48,96,86,68,
		57,82,63,70,
		37,34,83,27,
		19,97,9,17,
	}
	var min int
	for i, val := range x {
		if i == 0 || val < min {
			min = val
		}
	}
	fmt.Println(min)
}
