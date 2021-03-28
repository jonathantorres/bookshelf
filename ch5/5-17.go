package main

import (
	"fmt"
	"io"
	"net/http"
	"os"

	"golang.org/x/net/html"
)

func main() {
	if len(os.Args) < 3 {
		fmt.Fprintf(os.Stderr, "usage: prog url tags\n")
		os.Exit(1)
	}
	url := os.Args[1]
	tags := os.Args[2:]
	resp, err := http.Get(url)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		os.Exit(1)
	}
	defer resp.Body.Close()

	doc, err := html.Parse(resp.Body)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		os.Exit(1)
	}
	elems := ElementsByTagName(doc, tags...)
	fmt.Println(elems)
	if len(elems) > 0 {
		for _, e := range elems {
			printNode(os.Stdout, e)
		}
	}
}

func ElementsByTagName(doc *html.Node, names ...string) []*html.Node {
	tags := make([]*html.Node, 0, 10)
	forEachNode(doc, findElementsByTag, nil, tags, names...)
	return tags
}

func forEachNode(n *html.Node, pre, post func(n *html.Node, tags []*html.Node, names ...string), tags []*html.Node, names ...string) {
	if pre != nil {
		pre(n, tags, names...)
	}

	for c := n.FirstChild; c != nil; c = c.NextSibling {
		forEachNode(c, pre, post, tags, names...)
	}

	if post != nil {
		post(n, tags, names...)
	}
}

func findElementsByTag(n *html.Node, tags []*html.Node, names ...string) {
	if n != nil && n.Type == html.ElementNode {
		for _, name := range names {
			if name == n.Data {
				fmt.Println("tag found", n.Data)
				tags = append(tags, n)
			}
		}
	}
}

func printNode(o io.Writer, n *html.Node) {
	if n == nil {
		fmt.Fprintf(o, "<nil>\n")
		return
	}
	if n.Type == html.ElementNode {
		fmt.Fprintf(o, "<%s", n.Data)
		for _, a := range n.Attr {
			fmt.Fprintf(o, " %s", a.Key)
			if a.Val != "" {
				fmt.Fprintf(o, "=\"%s\"", a.Val)
			}
		}
		fmt.Fprintf(o, "></%s>\n", n.Data)
	}
}
