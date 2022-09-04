package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	if len(os.Args) == 1 {
		fsize(".")
		os.Exit(0)
	}
	for i, f := range os.Args {
		if i == 0 {
			continue
		}
		fsize(f)
	}
}

func fsize(f string) {
	fi, err := os.Stat(f)
	if err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	if fi.IsDir() {
		files, err := ioutil.ReadDir(f)
		if err != nil {
			fmt.Printf("%s\n", err)
			os.Exit(1)
		}
		for _, file := range files {
			fmt.Printf("%s %d bytes\n", file.Name(), file.Size())
		}
		return
	}
	fmt.Printf("%s %d bytes\n", fi.Name(), fi.Size())
}
