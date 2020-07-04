package main

// Exercise 5.5

import (
	"fmt"
	"golang.org/x/net/html"
	"net/http"
	"os"
	"strings"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: countwordsandimages [url]\n")
		os.Exit(1)
	}
	for _, url := range os.Args[1:] {
		w, i, err := CountWordsAndImages(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "error! %s\n", err)
			continue
		}
		fmt.Printf("%s: %d words and %d images\n", url, w, i)
	}
}

func CountWordsAndImages(url string) (words, images int, err error) {
	resp, err := http.Get(url)
	if err != nil {
		return
	}
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		err = fmt.Errorf("parsing HTML: %s", err)
		return
	}
	words, images = countWordsAndImages(doc)
	return
}

func countWordsAndImages(n *html.Node) (words, images int) {
	if n.Type == html.ElementNode && n.Data == "img" {
		images++
	}
	if n.Type == html.TextNode {
		splits := strings.Split(n.Data, " ")
		for _, str := range splits {
			s := strings.TrimSpace(str)
			if s != "" {
				words++
			}
		}
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		w, i := countWordsAndImages(c)
		images += i
		words += w
	}
	return
}
