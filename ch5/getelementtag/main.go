package main

// Exercise 5.17

import (
	"fmt"
	"golang.org/x/net/html"
	"net/http"
	"os"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: getelementtag [url]\n")
		os.Exit(1)
	}
	var tagToFind string = "p"
	for _, url := range os.Args[1:] {
		elems, err := getElementByTagName(url, tagToFind)
		if err != nil {
			fmt.Fprintf(os.Stderr, "error %s\n", err)
			continue
		}
		if len(elems) == 0 {
			fmt.Printf("tag <%s> was not found in %s\n", tagToFind, url)
			continue
		}
		fmt.Printf("%s:\n", url)
		for _, tag := range elems {
			fmt.Printf("%s\n", tag)
		}
	}
}

func getElementByTagName(url string, find ...string) ([]string, error) {
	var matches = make([]string, 0)
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		return nil, fmt.Errorf("parsing HTML: %s", err)
	}
	tags := ElementsByTagName(doc, find...)
	for _, elem := range tags {
		elemStr := ""
		if elem != nil {
			elemStr = fmt.Sprintf("<%s", elem.Data)
			for _, attr := range elem.Attr {
				elemStr += fmt.Sprintf(" %s=\"%s\"", attr.Key, attr.Val)
			}
			elemStr += fmt.Sprintf("></%s>", elem.Data)
		}
		if elemStr != "" {
			matches = append(matches, elemStr)
		}
	}
	return matches, nil
}

func ElementsByTagName(node *html.Node, find ...string) []*html.Node {
	var found = make([]*html.Node, 0)
	if len(find) == 0 {
		return found
	}
	var call func(*html.Node)
	call = func(n *html.Node) {
		for _, f := range find {
			if n.Type == html.ElementNode && n.Data == f {
				found = append(found, n)
			}
		}
		for c := n.FirstChild; c != nil; c = c.NextSibling {
			call(c)
		}
	}
	call(node)
	return found
}
