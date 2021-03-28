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
		fmt.Fprintf(os.Stderr, "usage: prog id url\n")
		os.Exit(1)
	}
	id := os.Args[1]
	url := os.Args[2]
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
	e := ElementById(doc, id)
	if e != nil {
		printNode(os.Stdout, e)
		return
	}
	fmt.Fprintf(os.Stderr, "#%s was not found in %s\n", id, url)
}

func ElementById(doc *html.Node, id string) *html.Node {
	return forEachNode(doc, findElement, nil, id)
}

func forEachNode(n *html.Node, pre, post func(n *html.Node, id string) bool, id string) *html.Node {
	if pre != nil {
		c := pre(n, id)
		if !c {
			return n
		}
	}

	for c := n.FirstChild; c != nil; c = c.NextSibling {
		n = forEachNode(c, pre, post, id)
		if n != nil {
			return n
		}
	}

	if post != nil {
		c := post(n, id)
		if !c {
			return n
		}
	}
	return nil
}

func findElement(n *html.Node, id string) bool {
	if n != nil && n.Type == html.ElementNode && len(n.Attr) > 0 {
		for _, a := range n.Attr {
			if a.Key == "id" && a.Val == id {
				return false
			}
		}
	}
	return true
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
