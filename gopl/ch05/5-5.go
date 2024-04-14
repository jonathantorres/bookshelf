package main

import (
	"bufio"
	"fmt"
	"net/http"
	"os"
	"strings"

	"golang.org/x/net/html"
)

func main() {
	for _, url := range os.Args[1:] {
		w, i, err := CountWordsAndImages(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "error counting %s: %s\n", url, err)
			continue
		}
		fmt.Printf("%s - words: %d, images: %d\n", url, w, i)
	}
}

func countWordsAndImages(n *html.Node) (words, images int) {
	if n.Type == html.ElementNode && n.Data == "img" {
		images++
	}
	if n.Type == html.TextNode {
		data := strings.TrimSpace(n.Data)
		s := bufio.NewScanner(strings.NewReader(data))
		s.Split(bufio.ScanWords)
		for s.Scan() {
			if s.Text() != "" {
				words++
			}
		}
		if err := s.Err(); err != nil {
			words, images = 0, 0
			return
		}
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		w, i := countWordsAndImages(c)
		words += w
		images += i
	}
	return
}

func CountWordsAndImages(url string) (words, images int, err error) {
	resp, err := http.Get(url)
	if err != nil {
		return
	}
	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		err = fmt.Errorf("parsing HTML: %s", err)
		return
	}
	words, images = countWordsAndImages(doc)
	return
}
