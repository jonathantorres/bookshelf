package main

import (
	"fmt"
	"io"
	"net/http"
	"net/url"
	"os"
	"time"
)

func main() {
	start := time.Now()
	ch := make(chan string)
	for _, url := range os.Args[1:] {
		go fetch(url, ch) // start a goroutine
	}
	for range os.Args[1:] {
		fmt.Println(<-ch) // receive from channel ch
	}
	fmt.Printf("%.2fs elapsed\n", time.Since(start).Seconds())
}

func fetch(furl string, ch chan<- string) {
	start := time.Now()
	resp, err := http.Get(furl)
	if err != nil {
		ch <- fmt.Sprint(err) // send to channel ch
		return
	}
	purl, err := url.Parse(furl)
	if err != nil {
		ch <- fmt.Sprintf("error parsing url %s: %v", furl, err)
		return
	}
	f, err := os.Create(purl.Hostname() + ".txt")
	if err != nil {
		ch <- fmt.Sprintf("error opening file for %s: %v", furl, err)
		return
	}
	nbytes, err := io.Copy(f, resp.Body)
	resp.Body.Close() // don't leak resources
	if err != nil {
		ch <- fmt.Sprintf("while reading %s: %v", furl, err)
		return
	}
	secs := time.Since(start).Seconds()
	ch <- fmt.Sprintf("%.2fs  %7d  %s", secs, nbytes, furl)
}
