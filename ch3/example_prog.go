package main

import (
	"fmt"
)

// takes a number entered by the user
// and doubles it
func main() {
	fmt.Print("Enter a number: ")
	var input float64
	fmt.Scanf("%f", &input)

	output := input * 2

	fmt.Println(output)
}
