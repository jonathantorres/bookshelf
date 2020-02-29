package main

import (
	"fmt"
)

// convert feet value into meters
func main() {
	var feet float64
	var meters float64

	fmt.Print("Enter amount of feets: ")
	fmt.Scanf("%f", &feet)

	meters = feet / 3.28
	fmt.Println("Amount of meters is: ", meters)
}
