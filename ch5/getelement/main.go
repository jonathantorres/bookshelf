package main

// Exercise 5.8

import (
	"fmt"
	"golang.org/x/net/html"
	"net/http"
	"os"
)

var idToFind string = "page"
var nodeFound *html.Node

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: getelement [url]\n")
		os.Exit(1)
	}
	for _, url := range os.Args[1:] {
		elem, err := getElementById(url, idToFind)
		if err != nil {
			fmt.Fprintf(os.Stderr, "error %s\n", err)
			continue
		}
		if elem != "" {
			fmt.Printf("%s: found %s\n", url, elem)
		} else {
			fmt.Printf("%s id was not found in %s\n", idToFind, url)
		}
	}
}

func ElementByID(doc *html.Node, id string) *html.Node {
	forEachNode(doc, findElement, nil)
	return nodeFound
}

func getElementById(url string, id string) (string, error) {
	resp, err := http.Get(url)
	if err != nil {
		return "", err
	}
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		return "", fmt.Errorf("parsing HTML: %s", err)
	}
	elem := ElementByID(doc, id)
	elemStr := ""
	if elem != nil {
		elemStr = fmt.Sprintf("<%s", elem.Data)
		for _, attr := range elem.Attr {
			elemStr += fmt.Sprintf(" %s=\"%s\"", attr.Key, attr.Val)
		}
		elemStr += fmt.Sprintf("></%s>", elem.Data)
	}
	return elemStr, nil
}

func findElement(n *html.Node) bool {
	if n.Type == html.ElementNode && len(n.Attr) > 0 {
		for _, attr := range n.Attr {
			if attr.Key == "id" && attr.Val == idToFind {
				nodeFound = n
				return true
			}
		}
	}
	return false
}

func forEachNode(n *html.Node, pre, post func(n *html.Node) bool) {
	if pre != nil {
		if preStop := pre(n); preStop {
			return
		}
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		forEachNode(c, pre, post)
	}
	if post != nil {
		if postStop := post(n); postStop {
			return
		}
	}
}
