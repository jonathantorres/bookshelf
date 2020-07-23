package main

// Exercise 8.3

import (
	"io"
	"log"
	"net"
	"os"
)

func main() {
	conn, err := net.Dial("tcp", "localhost:9999")
	if err != nil {
		log.Fatal(err)
	}
	tcpConn := conn.(*net.TCPConn) // type assertion
	done := make(chan struct{})
	go func() {
		io.Copy(os.Stdout, tcpConn)
		log.Println("done")
		done <- struct{}{}
	}()
	mustCopy(tcpConn, os.Stdin)
	tcpConn.CloseWrite()
	<-done
}

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		if err == io.EOF {
			return
		}
		log.Fatal(err)
	}
}
