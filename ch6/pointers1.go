package main

import (
	"fmt"
)

func main() {
	x := 5
	// we're passing a pointer to the value of x
	// this way, we can modify the variable directly
	// another way of calling this is "to pass the value by reference"
	zero(&x)
	fmt.Println(x)
}

func zero(x *int) {
	*x = 0
}
