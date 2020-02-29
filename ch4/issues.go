package main

import (
	"fmt"
	"os"
	"vamos/go_programming/ch4/github"
)

func main() {
	result, err := github.SearchIssues(os.Args[1:])
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Printf("%d issues: \n", result.TotalCount)
	for _, item := range result.Items {
		fmt.Printf("#%-5d %9.9s %.55s\n", item.Number, item.User.Login, item.Title)
	}
}
