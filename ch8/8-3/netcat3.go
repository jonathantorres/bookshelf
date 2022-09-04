package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
)

func main() {
	conn, err := net.Dial("tcp", "localhost:9090")
	if err != nil {
		log.Fatal(err)
	}
	done := make(chan struct{})
	go func() {
		io.Copy(os.Stdout, conn) // NOTE: ignoring errors
		log.Println("done")
		done <- struct{}{} // signal the main goroutine
	}()
	mustCopy(conn, os.Stdin)
	err = closeWrite(conn)
	if err != nil {
		log.Printf("%s", err)
	}
	<-done // wait for background goroutine to finish
}

func closeWrite(conn net.Conn) error {
	if conn, ok := conn.(*net.TCPConn); ok {
		return conn.CloseWrite()
	}
	return fmt.Errorf("interface not holding a *net.TCPConn value")
}

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}
