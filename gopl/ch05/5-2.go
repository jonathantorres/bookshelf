package main

import (
	"fmt"
	"os"

	"golang.org/x/net/html"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "findlinks1: %v\n", err)
		os.Exit(1)
	}
	mapping := make(map[string]int)
	mapElems(mapping, doc)
	for k, v := range mapping {
		fmt.Printf("%s: %d\n", k, v)
	}
}

func mapElems(mapping map[string]int, n *html.Node) {
	if n.Type == html.ElementNode {
		mapping[n.Data]++
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		mapElems(mapping, c)
	}
}
