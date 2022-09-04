package main

import "fmt"

func main() {
	var fahr, celsius float64
	var lower, upper, step int

	upper = 300
	step = 20
	fahr = float64(lower)

	fmt.Printf("Fahrenheit\tCelsius\n")
	for {
		if fahr > float64(upper) {
			break
		}
		celsius = toCelsius(fahr)
		fmt.Printf("%3.0f\t\t%6.1f\n", fahr, celsius)
		fahr = fahr + float64(step)
	}
}

func toCelsius(fahr float64) float64 {
	return (5.0 / 9.0) * (fahr - 32.0)
}
