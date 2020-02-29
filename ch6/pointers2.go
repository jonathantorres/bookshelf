package main

import (
	"fmt"
)

func main() {
	// the new() function also creates
	// a pointer to the value of x (in this case x = 0)
	x := new(int)
	one(x)
	fmt.Println(*x)
}

func one(x *int) {
	*x = 1
}
