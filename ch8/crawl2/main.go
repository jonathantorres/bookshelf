package main

// Exercise 8.6

import (
	"flag"
	"fmt"
	"github.com/jonathantorres/gopl/ch5/links"
	"log"
	"os"
	"sync"
)

var tokens = make(chan struct{}, 20)
var maxDepth int
var seen = make(map[string]bool)
var seenLock = sync.Mutex{}

func main() {
	flag.IntVar(&maxDepth, "d", 3, "max crawl depth")
	flag.Parse()
	if len(os.Args) == 1 {
		fmt.Fprintf(os.Stderr, "usage: crawl urls\n")
		os.Exit(1)
	}
	wg := &sync.WaitGroup{}
	for _, link := range flag.Args() {
		wg.Add(1)
		go crawl(link, 0, wg)
	}
	wg.Wait()
}

func crawl(url string, depth int, wg *sync.WaitGroup) {
	defer wg.Done()
	fmt.Println(depth, url)
	if depth >= maxDepth {
		return
	}
	tokens <- struct{}{}
	list, err := links.Extract(url)
	<-tokens
	if err != nil {
		log.Print(err)
	}
	for _, link := range list {
		seenLock.Lock()
		if seen[link] {
			seenLock.Unlock()
			continue
		}
		seen[link] = true
		seenLock.Unlock()
		wg.Add(1)
		go crawl(link, depth+1, wg)
	}
}
