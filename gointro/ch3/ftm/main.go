package main

import "fmt"

// convert from feet to meters
func main() {
	var feet float64
	var meters float64
	fmt.Print("Enter feet: ")
	fmt.Scanf("%f", &feet)
	meters = feet * 0.3048
	fmt.Println("Meters = ", meters)
}
