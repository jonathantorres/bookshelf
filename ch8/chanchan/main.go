package main

import (
	"fmt"
)

func main() {
	wait := make(chan int)
	go func() {
		fmt.Println("hi, from go routine")
		wait <- 1
	}()
	fmt.Println("hi, from main")
	var v int
	v = <-wait
	fmt.Println(v)
}
