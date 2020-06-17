package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println("start")
	Sleep(10)
	fmt.Println("end")
}

func Sleep(secs int64) {
	select {
	case <-time.After(time.Second * time.Duration(secs)):
		break
	}
}
