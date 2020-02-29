package main

import (
	"fmt"
)

func main() {
	// a switch statement inside the for loop
	for i := 0; i <= 5; i++ {
		switch i {
		case 0:
			fmt.Println("Zero")
		case 1:
			fmt.Println("One")
		case 2:
			fmt.Println("Two")
		case 3:
			fmt.Println("Three")
		case 4:
			fmt.Println("Four")
		case 5:
			fmt.Println("Five")
		}
	}
}
