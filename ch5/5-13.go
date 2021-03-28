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

var topLevel []string

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "No pages to crawl\n")
		os.Exit(1)
	}
	args := os.Args[1:]
	for _, arg := range args {
		u, err := url.Parse(arg)
		if err != nil {
			continue
		}
		topLevel = append(topLevel, u.Hostname())
	}
	breadthFirst(crawl, args)
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

func crawl(rawurl string) []string {
	savePage(rawurl)
	list, err := links.Extract(rawurl)
	if err != nil {
		log.Printf("%v\n", err)
	}
	return list
}

func savePage(rawurl string) {
	fmt.Println(rawurl)
	if !isTopLevel(rawurl) {
		return
	}
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
	path := u.Hostname() + path.Dir(u.Path)
	err = os.MkdirAll(path, 0777)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		os.Exit(1)
	}
	f, err := os.Create(path + "/" + fileName)
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
	for _, u := range topLevel {
		if strings.Contains(uri, u) {
			return true
		}
	}
	return false
}
