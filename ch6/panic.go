package main

import (
	"fmt"
)

func main() {
	// panic("PANIC!")

	// this line will never execute,
	// thanks to the panic() above
	// str := recover()
	// fmt.Println(str)

	// defering a function to recover
	// from the panic() call
	defer func() {
		str := recover()
		fmt.Println(str)
	}()
	panic("PANIC")
}
