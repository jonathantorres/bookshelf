package main

import "fmt"

func one(ptr *int) {
	*ptr = 1
}

func main() {
	num := new(int)
	*num = 100
	fmt.Println(*num)
	one(num)
	fmt.Println(*num)
}
