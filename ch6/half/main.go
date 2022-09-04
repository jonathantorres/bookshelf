package main

import "fmt"

func half(num int) (int, bool) {
	if num == 0 {
		return 0, true
	}
	var isEven bool
	if num%2 == 0 {
		isEven = true
	} else {
		isEven = false
	}
	return num / 2, isEven
}

func main() {
	fmt.Println(half(0))
	fmt.Println(half(1))
	fmt.Println(half(2))
}
