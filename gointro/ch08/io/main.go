package main

import (
	"io"
	"os"
	"strings"
)

func main() {
	r := strings.NewReader("My name is Jonathan\n")
	io.Copy(os.Stdout, r)
}
