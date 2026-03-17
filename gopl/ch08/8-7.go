package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"net/url"
	"os"
	"path"
	"strings"

	"github.com/jonathantorres/gopl/ch5/links"
)

var pageRoot string

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "usage: 8-7 [url]\n")
		os.Exit(1)
	}
	pageURL := os.Args[1]
	u, err := url.Parse(pageURL)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	pageRoot = u.Hostname()
	worklist := make(chan []string)
	unseenLinks := make(chan string)

	go func() { worklist <- []string{pageURL} }()

	for i := 0; i < 20; i++ {
		go func() {
			for link := range unseenLinks {
				foundLinks := crawl(link)
				go func() { worklist <- foundLinks }()
			}
		}()
	}

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

func crawl(rawurl string) []string {
	go savePage(rawurl)
	list, err := links.Extract(rawurl)
	if err != nil {
		log.Printf("%v\n", err)
	}
	var filteredList []string
	for _, l := range list {
		if isTopLevel(l) {
			filteredList = append(filteredList, l)
		}
	}
	return filteredList
}

func savePage(rawurl string) {
	fmt.Println(rawurl)
	u, err := url.Parse(rawurl)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		return
	}
	resp, err := http.Get(rawurl)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		return
	}
	defer resp.Body.Close()

	fileName := path.Base(u.Path)
	if u.Path == "" || u.Path == "/" || strings.HasSuffix(u.Path, "/") || !strings.Contains(u.Path, ".") {
		fileName = "index.html"
	}
	filePath := u.Hostname() + "/" + u.Path
	err = os.MkdirAll(filePath, 0777)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		os.Exit(1)
	}
	f, err := os.Create(filePath + "/" + fileName)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		return
	}
	_, err = io.Copy(f, resp.Body)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		return
	}
}

func isTopLevel(uri string) bool {
	u, err := url.Parse(uri)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		return false
	}
	if u.Hostname() == pageRoot {
		return true
	}
	return false
}
