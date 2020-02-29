package main

import (
	"fmt"
)

var literal_slice = []int{1, 2, 3, 4}

func main() {
	fmt.Println(literal_slice)
	for k, v := range literal_slice {
		fmt.Println(k, v)
	}
}
