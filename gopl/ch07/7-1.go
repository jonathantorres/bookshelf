package main

import (
	"bufio"
	"bytes"
	"fmt"
)

func main() {
	var wc WordCounter
	var lc LineCounter
	wc.Write([]byte("Jonathan Torres"))
	lc.Write([]byte("First line\nSecond line\nThird line"))
	fmt.Println(wc)
	fmt.Println(lc)
}

type WordCounter int
type LineCounter int

func (c *WordCounter) Write(p []byte) (int, error) {
	r := bytes.NewReader(p)
	s := bufio.NewScanner(r)
	s.Split(bufio.ScanWords)
	for s.Scan() {
		*c++
	}
	if err := s.Err(); err != nil {
		return 0, nil
	}
	return len(p), nil
}

func (c *LineCounter) Write(p []byte) (int, error) {
	r := bytes.NewReader(p)
	s := bufio.NewScanner(r)
	for s.Scan() {
		*c++
	}
	if err := s.Err(); err != nil {
		return 0, nil
	}
	return len(p), nil
}
