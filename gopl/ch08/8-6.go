package main

import (
	"flag"
	"fmt"
	"log"

	"github.com/jonathantorres/gopl/ch5/links"
)

var depth = flag.Int("depth", 0, "specify depth of the crawler")

func main() {
	flag.Parse()
	worklist := make(chan []string)  // lists of URLs, may have duplicates
	unseenLinks := make(chan string) // de-duplicated URLs
	var curDepth int

	// Add command-line arguments to worklist.
	go func() { worklist <- flag.Args() }()

	// Create 20 crawler goroutines to fetch each unseen link.
	for i := 0; i < 20; i++ {
		go func() {
			for link := range unseenLinks {
				foundLinks := crawl(link, &curDepth)
				go func() { worklist <- foundLinks }()
			}
		}()
	}

	// The main goroutine de-duplicates worklist items
	// and sends the unseen ones to the crawlers.
	seen := make(map[string]bool)
	for list := range worklist {
		for _, link := range list {
			if !seen[link] {
				seen[link] = true
				unseenLinks <- link
			}
		}
	}
}

func crawl(url string, curDepth *int) []string {
	fmt.Printf("(%d) %s\n", *curDepth, url)
	if *depth > 0 && *curDepth >= *depth {
		return nil
	}
	*curDepth++
	list, err := links.Extract(url)
	if err != nil {
		log.Print(err)
	}
	return list
}
