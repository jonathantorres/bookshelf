package main

import (
	"fmt"
	"os"
	"strings"

	"golang.org/x/net/html"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "findlinks1: %v\n", err)
		os.Exit(1)
	}
	printTextNodes(doc)
}

func printTextNodes(n *html.Node) {
	if n.Type == html.TextNode && n.Parent.Data != "script" && n.Parent.Data != "style" {
		data := strings.TrimSpace(n.Data)
		if data != "" {
			fmt.Println(data)
		}
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		printTextNodes(c)
	}
}
