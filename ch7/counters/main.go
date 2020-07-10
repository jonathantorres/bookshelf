package main

// Exercise 7.1

import (
	"bufio"
	"bytes"
	"fmt"
)

type WordCounter int64
type LineCounter int64

func (c *WordCounter) Write(p []byte) (int, error) {
	scanner := bufio.NewScanner(bytes.NewReader(p))
	scanner.Split(bufio.ScanWords)
	for scanner.Scan() {
		*c++
	}
	if err := scanner.Err(); err != nil {
		return 0, err
	}
	return len(p), nil
}

func (c *LineCounter) Write(p []byte) (int, error) {
	scanner := bufio.NewScanner(bytes.NewReader(p))
	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		*c++
	}
	if err := scanner.Err(); err != nil {
		return 0, err
	}
	return len(p), nil
}

func main() {
	var wc WordCounter
	fmt.Fprintf(&wc, "hello world")
	fmt.Println(wc)

	var lc LineCounter
	fmt.Fprintf(&lc, "hi\nwhat's my name again?\nOh yes! I remember")
	fmt.Println(lc)
}
