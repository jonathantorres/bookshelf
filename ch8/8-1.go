package main

import (
	"fmt"
	"io"
	"os"
)

func main() {
	if len(os.Args) == 1 {
		filecopy(os.Stdin, os.Stdout)
		return
	}
	for i, f := range os.Args {
		if i == 0 {
			continue
		}
		file, err := os.Open(f)
		if err != nil {
			fmt.Printf("%s\n", err)
			os.Exit(1)
		}
		filecopy(file, os.Stdout)
		err = file.Close()
		if err != nil {
			fmt.Printf("%s\n", err)
			os.Exit(1)
		}
	}
}

func filecopy(from io.Reader, to io.Writer) {
	_, err := io.Copy(to, from)
	if err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
}
