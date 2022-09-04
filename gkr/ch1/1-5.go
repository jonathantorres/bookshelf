package main

import "fmt"

func main() {
	var fahr float64

	fmt.Printf("Fahrenheit\tCelsius\n")
	for fahr = 300.0; fahr >= 0.0; fahr = fahr - 20.0 {
		fmt.Printf("%3.0f\t\t%6.1f\n", fahr, (5.0/9.0)*(fahr-32))
	}
}
