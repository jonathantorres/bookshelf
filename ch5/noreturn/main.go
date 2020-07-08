package main

// Exercise 5.19

import (
	"fmt"
)

func main() {
	defer func() {
		p := recover()
		fmt.Println(p)
	}()
	noreturn()
}

func noreturn() {
	panic("FAILURE!")
}
