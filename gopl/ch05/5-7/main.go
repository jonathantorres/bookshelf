package main

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"strings"

	"golang.org/x/net/html"
)

func main() {
	for _, url := range os.Args[1:] {
		err := outline(url, os.Stdout)
		if err != nil {
			fmt.Fprintf(os.Stderr, "outline: %v\n", err)
			continue
		}
	}
}

func outline(url string, out io.Writer) error {
	resp, err := http.Get(url)
	if err != nil {
		return err
	}
	defer resp.Body.Close()
	doc, err := html.Parse(resp.Body)
	if err != nil {
		return err
	}
	forEachNode(doc, startElement, endElement, out)
	return nil
}

func forEachNode(n *html.Node, pre, post func(n *html.Node, o io.Writer), o io.Writer) {
	if pre != nil {
		pre(n, o)
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		forEachNode(c, pre, post, o)
	}
	if post != nil {
		post(n, o)
	}
}

var depth int

// Develop startElement and endElement into a general HTML pretty-printer.
// Print comment nodes, text nodes, and the attributes of each element (<a href='...'>). Use
// short forms like <img/> instead of <img></img> when an element has no children. Write a
// test to ensure that the output can be parsed successfully.

func startElement(n *html.Node, o io.Writer) {
	if n.Type == html.ElementNode {
		fmt.Fprintf(o, "%*s<%s", depth*2, "", n.Data)
		if len(n.Attr) > 0 {
			for _, a := range n.Attr {
				fmt.Fprintf(o, " %s", a.Key)
				if a.Val != "" {
					fmt.Fprintf(o, "=\"%s\"", a.Val)
				}
			}
		}
		if n.FirstChild != nil {
			fmt.Fprintf(o, ">\n")
		} else {
			fmt.Fprintf(o, "/>\n")
		}
		depth++
	}
	if n.Type == html.DoctypeNode {
		fmt.Fprintf(o, "<!DOCTYPE ")
		fmt.Fprintf(o, strings.TrimSpace(n.Data))
		fmt.Fprintf(o, ">\n")
	}
	if n.Type == html.CommentNode {
		fmt.Fprintf(o, "<!-- ")
		fmt.Fprintf(o, strings.TrimSpace(n.Data))
		fmt.Fprintf(o, " -->")
	}
	if n.Type == html.TextNode {
		data := strings.TrimSpace(n.Data)
		if data != "" {
			fmt.Fprintf(o, "%*s%s", depth*2, "", data)
		}
	}
}

func endElement(n *html.Node, o io.Writer) {
	if n.Type == html.ElementNode {
		depth--
		if n.FirstChild != nil {
			fmt.Fprintf(o, "%*s</%s>\n", depth*2, "", n.Data)
		}
	}
}
