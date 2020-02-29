package main

import (
	"fmt"
	"os"
)

func main() {
	file, err := os.Open("text.txt")
	if err != nil {
		fmt.Println("There was a problem opening the file")
		os.Exit(1)
	}
	defer file.Close()

	stat, err := file.Stat()
	if err != nil {
		fmt.Println("There was a problem getting the details from the file")
		os.Exit(1)
	}

	bs := make([]byte, stat.Size())
	_, err = file.Read(bs)
	if err != nil {
		fmt.Println("There was a problem reading the file")
		os.Exit(1)
	}

	str := string(bs)
	fmt.Println(str)
}
