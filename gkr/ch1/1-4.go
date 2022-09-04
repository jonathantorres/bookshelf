package main

import "fmt"

func main() {
	var fahr, celsius float64
	var upper, step int

	upper = 300
	step = 20

	fmt.Printf("Celsius\t\tFahrenheit\n")
	for celsius <= float64(upper) {
		fahr = (((celsius * 9.0) / 5) + 32)
		fmt.Printf("%3.0f\t\t%6.1f\n", celsius, fahr)
		celsius = celsius + float64(step)
	}
}
