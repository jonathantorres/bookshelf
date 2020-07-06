package main

// Exercise 5.14

import (
	"fmt"
	"github.com/jonathantorres/gopl/ch5/links"
	"log"
	"os"
	"net/http"
	"strings"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: findlinks4 [url]\n")
		os.Exit(1)
	}
	breadthFirst(crawl, os.Args[1:])
}

func breadthFirst(f func(item string) []string, worklist []string) {
	seen := make(map[string]bool)
	for len(worklist) > 0 {
		items := worklist
		worklist = nil
		for _, item := range items {
			if !seen[item] {
				seen[item] = true
				worklist = append(worklist, f(item)...)
			}
		}
	}
}

func crawl(url string) []string {
	fmt.Println(url)
	list, err := links.Extract(url)
	if err != nil {
		log.Print(err)
	}
	makePages(url, list)
	return list
}

func makePages(root string, urls []string) {
	var dirName string
	var path string
	if strings.HasPrefix(root, "http://") {
		dirName = root[7:]
	} else if strings.HasPrefix(root, "https://") {
		dirName = root[8:]
	}
	if _, err := os.Stat("./"+dirName); err != nil {
		if os.IsNotExist(err) {
			if err = os.Mkdir(dirName, 0777); if != nil {
				fmt.Fprintf(os.Stderr, "error creating directory: %s", err)
				os.Exit(1)
			}
		}
	}
	for _, url := range urls {
		resp, err := http.Get(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "error getting %s: %s", url, err)
			continue
		}
		resp.Body.Close()
	}
	fmt.Println("dir:", dirName)
}
