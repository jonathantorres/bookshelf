package main

import "fmt"

func add(y []int) {
	y = append(y, 13, 16, 14)
}

func addref(y *[]int) {
	*y = append(*y, 22, 33, 44)
}

func main() {
	x := []int{
		4,5,6,
		99,34,8,
	}
	fmt.Println(x)
	add(x)
	fmt.Println(x)
	fmt.Println()
	fmt.Println(x)
	addref(&x)
	fmt.Println(x)
}
