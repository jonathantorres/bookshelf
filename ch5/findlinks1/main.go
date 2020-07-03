package main

// Exercise 5.1
// Exercise 5.2
// Exercise 5.4

import (
	"fmt"
	"golang.org/x/net/html"
	"os"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "findlinks1: %v\n", err)
		os.Exit(1)
	}
	for _, link := range visit(nil, doc) {
		fmt.Println(link)
	}
	fmt.Println()
	for k, v := range getMapping(nil, doc) {
		fmt.Printf("<%s></%s>: %d\n", k, k, v)
	}
}

func visit(links []string, n *html.Node) []string {
	if n == nil {
		return links
	}
	if n.Type == html.ElementNode {
		if n.Data == "a" || n.Data == "img" || n.Data == "link" || n.Data == "script" {
			for _, elem := range n.Attr {
				if elem.Key == "href" || elem.Key == "src" {
					links = append(links, elem.Val)
				}
			}
		}
	}
	links = visit(links, n.FirstChild)
	links = visit(links, n.NextSibling)
	return links
}

func getMapping(counts map[string]int, n *html.Node) map[string]int {
	if counts == nil {
		counts = make(map[string]int)
	}
	if n == nil {
		return counts
	}
	if n.Type == html.ElementNode {
		counts[n.Data]++
	}
	counts = getMapping(counts, n.FirstChild)
	counts = getMapping(counts, n.NextSibling)
	return counts
}
