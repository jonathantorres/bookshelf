package main

// Exercise 1.2

import (
	"fmt"
	"os"
)

func main() {
	for i, arg := range os.Args[:] {
		fmt.Println(i, arg)
	}
}
