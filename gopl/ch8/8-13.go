package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"time"
)

type client chan<- string // an outgoing message channel

var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) // all incoming client messages
)

func main() {
	listener, err := net.Listen("tcp", "localhost:9090")
	if err != nil {
		log.Fatal(err)
	}
	go broadcaster()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		case msg := <-messages:
			for cli := range clients {
				cli <- msg
			}
		case cli := <-entering:
			clients[cli] = true
		case cli := <-leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

func handleConn(conn net.Conn) {
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)
	who := conn.RemoteAddr().String()
	to := time.NewTimer(5 * time.Minute)
	chatC := make(chan struct{})
	ch <- "You are " + who
	messages <- who + " has arrived"
	entering <- ch
	var closed bool
	defer func() {
		if !closed {
			conn.Close()
		}
	}()
	go func() {
		for {
			select {
			case <-to.C:
				conn.Write([]byte("you're too quiet, bye!\n"))
				to.Stop()
				conn.Close()
				closed = true
				return
			case <-chatC:
				to = time.NewTimer(10 * time.Second)
			}
		}
	}()
	input := bufio.NewScanner(conn)
	for input.Scan() {
		messages <- who + ": " + input.Text()
		chatC <- struct{}{}
	}

	leaving <- ch
	messages <- who + " has left"
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}
