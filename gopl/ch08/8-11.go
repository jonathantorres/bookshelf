package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
	"sync"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: 8-11 [urls]")
		os.Exit(1)
	}
	var wg sync.WaitGroup
	numUrls := len(os.Args[1:])
	response := make(chan string, numUrls)
	cancel := make(chan struct{})
	for _, url := range os.Args[1:] {
		wg.Add(1)
		go func(url string) {
			defer wg.Done()
			resp, err := request(url, cancel)
			if err != nil {
				response <- fmt.Sprintf("%s\n", err)
				return
			}
			response <- string(resp)
		}(url)
	}
	r := <-response
	close(cancel)
	fmt.Printf("%s\n", r)
	wg.Wait()
}

func request(url string, cancel <-chan struct{}) ([]byte, error) {
	req, err := http.NewRequest("GET", url, nil)
	if err != nil {
		return nil, err
	}
	req.Cancel = cancel
	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()
	b, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return nil, err
	}
	return b, nil
}
