package main

import (
	"fmt"
)

func main() {
	msg := make(chan string)
	go func() {
		var gomsg string = "Hi!"
		msg <- gomsg
	}()
	fmt.Println(<-msg)
	fmt.Println("done")
}
