package main

import "fmt"

func main() {
	panic("WHOOPS!")
	msg := recover() // Nope, can't recover
	fmt.Println(msg)
}
