package main

// Exercise 5.12

import (
	"fmt"
	"golang.org/x/net/html"
	"net/http"
	"os"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: outline [url]\n")
		os.Exit(1)
	}
	for _, url := range os.Args[1:] {
		err := outline(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "error! %s\n", err)
			continue
		}
	}
}

func outline(url string) error {
	resp, err := http.Get(url)
	if err != nil {
		return err
	}
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		return fmt.Errorf("parsing HTML: %s", err)
	}
	var depth int
	forEachNode(doc, func(n *html.Node) {
		if n.Type == html.ElementNode {
			fmt.Printf("%*s<%s>\n", depth*2, "", n.Data)
			depth++
		}
	}, func(n *html.Node) {
		if n.Type == html.ElementNode {
			depth--
			fmt.Printf("%*s</%s>\n", depth*2, "", n.Data)
		}
	})
	return nil
}

func forEachNode(n *html.Node, pre, post func(n *html.Node)) {
	if pre != nil {
		pre(n)
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		forEachNode(c, pre, post)
	}
	if post != nil {
		post(n)
	}
}
