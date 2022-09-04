package main

import "fmt"

func main() {
	p := make([]int, 1000)
	for i, n := range p {
		fmt.Printf("%08X", n)
		if i%8 == 7 {
			fmt.Println()
		}
	}
	fmt.Println()
}
