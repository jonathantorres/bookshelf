package main

// Exercise 9.5

import (
	"fmt"
	"time"
)

func main() {
	message := make(chan string)
	go func() {
		for {
			time.Sleep(1*time.Second)
			message <- "ping"
			fmt.Println(<-message)
		}
	}()
	for {
		fmt.Println(<-message)
		time.Sleep(1*time.Second)
		message <- "pong"
	}
}
