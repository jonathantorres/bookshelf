package main

import "fmt"

func main() {
	// string assignment
	var x string
	x = "first"
	fmt.Println(x)
	x = "second"
	fmt.Println(x)

	// string concatenation
	var y string
	y = "first"
	fmt.Println(y)
	y = y + " second"
	fmt.Println(y)
	y += " and third"
	fmt.Println(y)
}
