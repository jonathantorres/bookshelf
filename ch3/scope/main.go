package main

import "fmt"

// this is a global variable
var msg string = "Hello!"

func main() {
	fmt.Println(msg)
	f()
}

// msg can also be used here
func f() {
	fmt.Println(msg)
}
