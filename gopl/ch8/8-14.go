package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
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

	ch <- "Please enter your name: "
	var who string
	_, err := fmt.Fscanf(conn, "%s", &who)
	if err != nil {
		who = conn.RemoteAddr().String()
		ch <- fmt.Sprintf("There was an error reading your name: %s", err)
		ch <- fmt.Sprintf("Using %s for now", who)
	}
	ch <- "You are " + who
	messages <- who + " has arrived"
	entering <- ch
	input := bufio.NewScanner(conn)
	for input.Scan() {
		txt := input.Text()
		if txt != "" {
			messages <- who + ": " + txt
		}
	}

	leaving <- ch
	messages <- who + " has left"
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}
