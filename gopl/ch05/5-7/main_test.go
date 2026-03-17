package main

import (
	"bytes"
	"testing"

	"golang.org/x/net/html"
)

func TestOutput(t *testing.T) {
	b := make([]byte, 0, 10)
	buf := bytes.NewBuffer(b)
	err := outline("http://www.golang.org", buf)
	if err != nil {
		t.Errorf("%v\n", err)
	}

	_, err = html.Parse(buf)
	if err != nil {
		t.Errorf("%v\n", err)
	}
}
