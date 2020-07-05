package main

// Exercise 5.7

import (
	"fmt"
	"golang.org/x/net/html"
	"net/http"
	"os"
	"strings"
)

var depth int

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: outline [url]\n")
		os.Exit(1)
	}
	for _, url := range os.Args[1:] {
		err := printOutline(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "error! %s\n", err)
			continue
		}
	}
}

func printOutline(url string) error {
	resp, err := http.Get(url)
	if err != nil {
		return err
	}
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		return fmt.Errorf("parsing HTML: %s", err)
	}
	forEachNode(doc, startElement, endElement)
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

func startElement(n *html.Node) {
	if n.Type == html.ElementNode {
		fmt.Printf("%*s<%s", depth*2, "", n.Data)
		if len(n.Attr) > 0 {
			for _, attr := range n.Attr {
				fmt.Printf(" %s=\"%s\"", attr.Key, attr.Val)
			}
		}
		if n.FirstChild != nil {
			fmt.Printf(">\n")
		}
		depth++
	}
	if n.Type == html.TextNode || n.Type == html.CommentNode {
		txt := strings.TrimSpace(n.Data)
		if txt != "" {
			fmt.Printf("%*s%s\n", depth*2, "", txt)
		}
	}
}

func endElement(n *html.Node) {
	if n.Type == html.ElementNode {
		depth--
		if n.FirstChild != nil {
			fmt.Printf("%*s</%s>\n", depth*2, "", n.Data)
		} else {
			fmt.Printf("/>\n")
		}
	}
}
