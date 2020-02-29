package main

import (
	"fmt"
)

// enter a fahrenheit temperature and convert it to celcius
func main() {
	var fahr float64
	var cel float64

	fmt.Print("Enter Fahrenheit temperature: ")
	fmt.Scanf("%f", &fahr)

	cel = (fahr - 32) * 5 / 9
	fmt.Println("Celcius Temperature is: ", cel)
}
