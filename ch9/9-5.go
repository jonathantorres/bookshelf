package main

import (
	"fmt"
	"sync"
)

// About 90,000 ping<->pong operations per second

func main() {
	p := make(chan string)
	var wg sync.WaitGroup
	wg.Add(1)
	go func() {
		for {
			p <- "ping"
			s := <-p
			fmt.Println(s)
		}
		wg.Done()
	}()
	wg.Add(1)
	go func() {
		for {
			s := <-p
			fmt.Println(s)
			p <- "pong"
		}
		wg.Done()
	}()
	wg.Wait()
}
