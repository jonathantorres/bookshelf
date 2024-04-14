package main

import (
	"fmt"
	"log"
	"os"
	"time"

	"github.com/jonathantorres/gopl/ch4/github"
)

func main() {
	day, _ := time.ParseDuration("24h")
	mAgo := time.Now().Add(day * -30)
	yAgo := time.Now().Add(day * -365)
	monthItems := make([]*github.Issue, 0, 10)
	yearItems := make([]*github.Issue, 0, 10)
	oldItems := make([]*github.Issue, 0, 10)
	result, err := github.SearchIssues(os.Args[1:])
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%d issues:\n", result.TotalCount)
	for _, item := range result.Items {
		if item.CreatedAt.Unix() >= mAgo.Unix() {
			monthItems = append(monthItems, item)
		} else if item.CreatedAt.Unix() >= yAgo.Unix() {
			yearItems = append(yearItems, item)
		} else {
			oldItems = append(oldItems, item)
		}
	}
	fmt.Printf("\nless than a month old items\n")
	for _, i := range monthItems {
		fmt.Printf("#%-5d %9.9s %.55s\n", i.Number, i.User.Login, i.Title)
	}

	fmt.Printf("\nless than a year old items\n")
	for _, i := range yearItems {
		fmt.Printf("#%-5d %9.9s %.55s\n", i.Number, i.User.Login, i.Title)
	}

	fmt.Printf("\nolder items\n")
	for _, i := range oldItems {
		fmt.Printf("#%-5d %9.9s %.55s\n", i.Number, i.User.Login, i.Title)
	}
}
