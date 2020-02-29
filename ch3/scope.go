package main

import (
	"fmt"
)

// this is a global variable
var x string = "Hello, World"

func main() {
	fmt.Println(x)
}

// x can also be used here :D
func f() {
	fmt.Println(x)
}
