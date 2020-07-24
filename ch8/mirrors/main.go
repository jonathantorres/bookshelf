package main

// Exercise 8.7

import (
	"fmt"
	"github.com/jonathantorres/gopl/ch5/links"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"strings"
)

var startDomain string

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: mirrors [url]\n")
		os.Exit(1)
	}
	worklist := make(chan []string)
	var n int
	n++
	go func() {
		worklist <- os.Args[1:]
	}()

	seen := make(map[string]bool)
	for ; n > 0; n-- {
		list := <-worklist
		for _, link := range list {
			if !seen[link] {
				seen[link] = true
				n++
				go func(link string) {
					worklist <- crawl(link)
				}(link)
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
	if startDomain == "" {
		startDomain = root
	}
	var dirName string
	if strings.HasPrefix(root, "http://") {
		dirName = root[7:]
	} else if strings.HasPrefix(root, "https://") {
		dirName = root[8:]
	}
	if startDomain != root {
		return
	}
	if _, err := os.Stat("./" + dirName); err != nil {
		if os.IsNotExist(err) {
			if err = os.Mkdir(dirName, 0777); err != nil {
				fmt.Fprintf(os.Stderr, "error creating directory: %s\n", err)
				os.Exit(1)
			}
		}
	}
	for _, url := range urls {
		resp, err := http.Get(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "error getting %s: %s\n", url, err)
			continue
		}
		host := resp.Request.URL.Host
		path := resp.Request.URL.Path
		var filename string
		var fullpath string
		if host == dirName {
			// same domain
			filename = getFilename(path)
			fullpath = dirName + path + filename
			if err = os.MkdirAll(dirName+path, 0777); err != nil {
				fmt.Fprintf(os.Stderr, "error creating path directories: %s\n", err)
				os.Exit(1)
			}
		} else if strings.Index(dirName, host) != -1 {
			// is under subdomain
			filename = getFilename(path)
			fullpath = dirName + "/" + host + path + filename
			if err = os.MkdirAll(dirName+host+path, 0777); err != nil {
				fmt.Fprintf(os.Stderr, "error creating path directories: %s\n", err)
				os.Exit(1)
			}
		} else {
			continue
		}
		if fullpath == "" {
			fmt.Fprintf(os.Stderr, "could not build full path for %s\n", url)
			continue
		}
		bodyData := make([]byte, 0)
		if bodyData, err = ioutil.ReadAll(resp.Body); err != nil {
			fmt.Fprintf(os.Stderr, "error reading response: %s\n", err)
			continue
		}
		resp.Body.Close()
		if err = ioutil.WriteFile(fullpath, bodyData, 0644); err != nil {
			fmt.Fprintf(os.Stderr, "error creating file: %s\n", err)
			continue
		}
	}
}

func getFilename(path string) string {
	var filename string
	if path == "/" || strings.HasPrefix(path, "/") {
		filename = "index.html"
	} else {
		lastIndex := strings.LastIndex(path, "/")
		if lastIndex != -1 {
			filename = path[lastIndex+1:]
		}
	}
	return filename
}
