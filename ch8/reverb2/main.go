package main

// Exercise 8.4

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"strings"
	"sync"
	"time"
)

func main() {
	l, err := net.Listen("tcp", "localhost:9999")
	if err != nil {
		log.Fatal(err)
	}
	for {
		conn, err := l.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

func handleConn(c net.Conn) {
	var wg sync.WaitGroup
	tcpConn := c.(*net.TCPConn)
	input := bufio.NewScanner(tcpConn)
	for input.Scan() {
		wg.Add(1)
		go func(c *net.TCPConn, shout string, delay time.Duration) {
			fmt.Fprintln(c, "\t", strings.ToUpper(shout))
			time.Sleep(delay)
			fmt.Fprintln(c, "\t", shout)
			time.Sleep(delay)
			fmt.Fprintln(c, "\t", strings.ToLower(shout))
			wg.Done()
		}(tcpConn, input.Text(), 1*time.Second)
	}
	wg.Wait()
	tcpConn.CloseWrite()
}
