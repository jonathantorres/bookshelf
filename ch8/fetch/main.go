package main

// Exercise 8.11

import (
	"flag"
	"fmt"
	"log"
	"net/http"
	"sync"
	"os"
)

var cancel chan struct{}
var responses chan *http.Response

func main() {
	flag.Parse()
	if len(flag.Args()) == 0 {
		fmt.Fprintf(os.Stderr, "usage: ./fetch [url]\n")
		os.Exit(1)
	}
	cancel = make(chan struct{})
	responses = make(chan *http.Response)
	wg := &sync.WaitGroup{}
	for _, url := range flag.Args() {
		wg.Add(1)
		go fetch(url, wg)
	}
	resp := <-responses
	defer resp.Body.Close()
	close(cancel)
	fmt.Println(resp.Request.URL)
	wg.Wait()
}

func fetch(url string, wg *sync.WaitGroup) {
	defer wg.Done()
	req, err := http.NewRequest("HEAD", url, nil)
	if err != nil {
		log.Printf("HEAD %s: %s", url, err)
		return
	}
	req.Cancel = cancel
	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		log.Printf("HEAD %s: %s", url, err)
		return
	}
	responses <- resp
}
