package main

import (
	"fmt"
	"io"
	"os"

	"golang.org/x/net/html"
)

type StringReader struct {
	s string
}

func (r *StringReader) Read(p []byte) (int, error) {
	if len(p) == 0 {
		return 0, nil
	}
	n := copy(p, r.s)
	r.s = r.s[n:]
	return n, io.EOF
}

func NewReader(s string) *StringReader {
	return &StringReader{
		s: s,
	}
}

var s string = `<!DOCTYPE html>
<html lang="en">
    <head>
        <title>Test</title>
    </head>
    <body>
        <div class="container">
            <div class="row main-intro">
                <div class="col-md-3">
                    <p>Stuff here</p>
                </div>
                <div class="col-md-9">
                    <a href="/stuff1">Link1</a>
                    <a href="/stuff2">Link2</a>
                    <a href="/stuff3">Link3</a>
                </div>
            </div>
        </div>
    </body>
</html>
`

func main() {
	doc, err := html.Parse(NewReader(s))
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: %v\n", err)
		os.Exit(1)
	}
	for _, link := range visit(nil, doc) {
		fmt.Println(link)
	}
}

// visit appends to links each link found in n and returns the result.
func visit(links []string, n *html.Node) []string {
	if n.Type == html.ElementNode && n.Data == "a" {
		for _, a := range n.Attr {
			if a.Key == "href" {
				links = append(links, a.Val)
			}
		}
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		links = visit(links, c)
	}
	return links
}
