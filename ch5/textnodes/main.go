package main

// Exercise 5.3

import (
	"fmt"
	"golang.org/x/net/html"
	"os"
	"strings"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "textnodes: %v\n", err)
		os.Exit(1)
	}
	for _, text := range getTextNodes(nil, doc) {
		fmt.Println(text)
	}
}

func getTextNodes(texts []string, n *html.Node) []string {
	if n == nil {
		return texts
	}
	if n.Type == html.TextNode {
		if n.Data != "script" && n.Data != "style" {
			texts = append(texts, strings.TrimSpace(n.Data))
		}
	}
	texts = getTextNodes(texts, n.FirstChild)
	texts = getTextNodes(texts, n.NextSibling)
	return texts
}
