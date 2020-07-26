package main

// Exercise 8.12
// Exercise 8.13
// Exercise 8.14
// Exercise 8.15

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"time"
)

type client chan<- string // an outgoing message channel
type clientData struct {
	online     bool
	name       string
	clientChan client
}

const timeout = 60 * time.Second

var clients map[client]clientData

var (
	entering = make(chan clientData)
	leaving  = make(chan clientData)
	messages = make(chan string) // all incoming client messages
)

func main() {
	listener, err := net.Listen("tcp", "localhost:9999")
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
	clients = make(map[client]clientData) // all connected clients
	for {
		select {
		case msg := <-messages:
			for cli := range clients {
				select {
				case cli <- msg:
					// incoming message
				default:
					// reading messages slowly
				}
				
			}
		case cli := <-entering:
			clients[cli.clientChan] = cli
		case cli := <-leaving:
			delete(clients, cli.clientChan)
			close(cli.clientChan)
		}
	}
}

func handleConn(conn net.Conn) {
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)

	who := clientData{
		online:     true,
		name:       conn.RemoteAddr().String(),
		clientChan: ch,
	}
	for _, clData := range clients {
		ch <- clData.name + " is also here"
	}
	fmt.Fprint(conn, "Please enter your name: ")
	nameInput := bufio.NewScanner(conn)
	for nameInput.Scan() {
		who.name = nameInput.Text()
		break
	}
	ch <- "You are " + who.name
	messages <- who.name + " has arrived"
	entering <- who
	timer := time.NewTimer(timeout)
	go func() {
		<-timer.C
		conn.Close()
	}()
	input := bufio.NewScanner(conn)
	for input.Scan() {
		messages <- who.name + ": " + input.Text()
		timer.Reset(timeout)
	}

	leaving <- who
	messages <- who.name + " has left"
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}
