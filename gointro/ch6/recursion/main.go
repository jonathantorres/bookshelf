package main

import "fmt"

func main() {
	fmt.Println(factorial(2))
}

func factorial(num uint) uint {
	if num == 0 {
		return 1
	}
	return num * factorial(num-1)
}
