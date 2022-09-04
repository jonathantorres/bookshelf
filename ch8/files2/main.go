package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	bs, err := ioutil.ReadFile("text.txt")
	if err != nil {
		fmt.Println(err.Error())
		os.Exit(1)
	}
	str := string(bs)
	fmt.Println(str)
}
