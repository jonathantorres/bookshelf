package main

import (
	"fmt"
)

// by using the defer keyword we are telling golang
// to execute the second() method after main() finishes
func main() {
	defer second()
	first()
}

func first() {
	fmt.Println("first")
}

func second() {
	fmt.Println("second")
}
