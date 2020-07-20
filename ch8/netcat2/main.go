package main

import (
	"io"
	"log"
	"net"
	"fmt"
	"os"
)

func main() {
	conn, err := net.Dial("tcp", "localhost:8010")
	if err != nil {
		log.Fatal(err)
	}
	defer conn.Close()
	n, err := io.Copy(os.Stdout, conn)
	if err != nil {
		fmt.Fprintf(os.Stderr, "error! %s\n", err)
	}
	fmt.Fprintf(os.Stdout, "%d bytes written\n", n)
}
