package main

import "fmt"

func main() {
	var x [5]float64 = [5]float64{
		55,
		34,
		11,
		88,
		90,
	}
	for i, val := range x {
		fmt.Println(i, val)
	}
	fmt.Println()

	y := [5]float64{
		55,
		34,
		11,
		88,
		90,
	}
	for i, val := range y {
		fmt.Println(i, val)
	}
}
