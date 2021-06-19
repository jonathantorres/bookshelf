package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	_, err := r.ReadByte()
	fmt.Printf("%d\n", err != io.EOF)
}
