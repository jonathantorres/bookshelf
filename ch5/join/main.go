package main

// Exercise 5.16

import (
	"fmt"
)

func main() {
	fmt.Println(join(",", "one", "two", "three"))
	fmt.Println(join(",", "me"))
	fmt.Println(join(","))
}

func join(sep string, elems ...string) string {
	if len(elems) == 0 {
		return ""
	}
	result := ""
	for i, ele := range elems {
		result += ele
		if len(elems) > 1 && i < len(elems)-1 {
			result += sep
		}
	}
	return result
}
