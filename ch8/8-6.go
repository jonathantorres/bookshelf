package main

import "fmt"

func main() {
	p := make([]byte, 10)
	for _, b := range p {
		fmt.Printf("%d\n", b)
	}
}
