package main

import (
	"fmt"
	"os"
)

func main() {
	file, err := os.Create("info.txt")
	defer file.Close()

	if err != nil {
		fmt.Println(err.Error())
		os.Exit(1)
	}

	if _, err := file.WriteString("This is the info file\n"); err != nil {
		fmt.Println(err.Error())
		os.Exit(1)
	}
	fmt.Println("Wrote file ok.")
}
