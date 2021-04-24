package main

import (
	"flag"
	"fmt"
)

// On my laptop (MacBook Pro with 8GB of memory)
// it can hold up to 100 million goroutines

var ng = flag.Int("n", 1, "Number of goroutines")

func main() {
	flag.Parse()
	var chans []chan int
	val := 0
	for i := 0; i < (*ng)-1; i++ {
		chans = append(chans, make(chan int))
	}
	for i, c := range chans {
		if i == 0 {
			go func(ch chan int, val int) {
				val++
				ch <- val
				close(ch)
			}(c, val)
			continue
		}
		if i <= len(chans)-1 {
			go func(ch1 chan int, ch2 chan int) {
				v := <-ch2
				v++
				ch1 <- v
				close(ch1)
			}(c, chans[i-1])
		}
	}
	if len(chans) > 0 {
		lastChan := chans[len(chans)-1]
		v := <-lastChan
		fmt.Println(v)
		return
	}
	fmt.Println(val)
}
