package main

import (
	"fmt"
	"net"
	"os"
	"strings"
	"sync"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "addresses must be provided\n")
		os.Exit(1)
	}
	var wg sync.WaitGroup
	for _, adr := range os.Args[1:] {
		if !strings.Contains(adr, "=") {
			fmt.Fprintf(os.Stderr, "invalid location or address\n")
			continue
		}
		parts := strings.Split(adr, "=")
		if len(parts) < 2 {
			fmt.Fprintf(os.Stderr, "invalid location or address\n")
			continue
		}
		loc := parts[0]
		addr := parts[1]
		wg.Add(1)
		go launchClient(loc, addr, &wg)
	}
	wg.Wait()
}

func launchClient(loc string, addr string, wg *sync.WaitGroup) {
	defer wg.Done()
	conn, err := net.Dial("tcp", addr)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		return
	}
	defer conn.Close()
	for {
		buf := make([]byte, 100)
		_, err = conn.Read(buf)
		if err != nil {
			fmt.Fprintf(os.Stderr, "%s\n", err)
			break
		}
		fmt.Fprintf(os.Stdout, "%s: %s", loc, string(buf))
	}
}
