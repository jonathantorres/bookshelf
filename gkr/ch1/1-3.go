package main

import "fmt"

func main() {
	var fahr, celsius float64
	var upper, step int

	upper = 300
	step = 20

	fmt.Printf("Fahrenheit\tCelcius\n")
	for fahr <= float64(upper) {
		celsius = (5.0 / 9.0) * (fahr - 32.0)
		fmt.Printf("%3.0f\t\t%6.1f\n", fahr, celsius)
		fahr = fahr + float64(step)
	}
}
