package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"strings"
	"time"
)

func main() {
	l, err := net.Listen("tcp", "localhost:9090")
	if err != nil {
		log.Fatal(err)
	}
	for {
		conn, err := l.Accept()
		if err != nil {
			log.Print(err) // e.g., connection aborted
			continue
		}
		go handleConn(conn)
	}
}

func echo(c net.Conn, shout string, delay time.Duration) {
	fmt.Fprintln(c, "\t", strings.ToUpper(shout))
	time.Sleep(delay)
	fmt.Fprintln(c, "\t", shout)
	time.Sleep(delay)
	fmt.Fprintln(c, "\t", strings.ToLower(shout))
}

func handleConn(c net.Conn) {
	input := bufio.NewScanner(c)
	to := time.NewTimer(10 * time.Second)
	echoC := make(chan struct{})
	var closed bool
	defer func() {
		if !closed {
			c.Close()
		}
	}()
	// goroutine to check for a timeout
	go func() {
		for {
			select {
			case <-to.C:
				c.Write([]byte("you're too quiet, bye!\n"))
				to.Stop()
				c.Close()
				closed = true
				return
			case <-echoC:
				to = time.NewTimer(10 * time.Second)
			}
		}
	}()
	for input.Scan() {
		echoC <- struct{}{}
		go echo(c, input.Text(), 1*time.Second)
	}
	if err := input.Err(); err != nil {
		log.Printf("%s", err)
		return
	}
}
