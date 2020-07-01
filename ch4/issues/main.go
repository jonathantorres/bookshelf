package main

// Exercise 4.10

import (
	"fmt"
	"time"
	"github.com/jonathantorres/gopl/ch4/github"
	"os"
)

const (
	lessThanAMonth = "less than a month old"
	lessThanAYear = "less than a year old"
	moreThanAYear = "more than a year old"
)

func main() {
	now := time.Now()
	issues := make(map[string][]*github.Issue)
	result, err := github.SearchIssues(os.Args[1:])
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Printf("%d issues: \n", result.TotalCount)
	for _, item := range result.Items {
		daysOld := int64(now.Sub(item.CreatedAt).Hours() / 24)
		switch {
		case daysOld < 30:
			issues[lessThanAMonth] = append(issues[lessThanAMonth], item)
		case daysOld > 30 && daysOld < 365:
			issues[lessThanAYear] = append(issues[lessThanAYear], item)
		default:
			issues[moreThanAYear] = append(issues[moreThanAYear], item)
		}
	}
	for k, v := range issues {
		fmt.Printf("%s:\n", k)
		for _, item := range v {
			y, m, d := item.CreatedAt.Date()
			dateStr := fmt.Sprintf("%v %d, %d", m, d, y)
			fmt.Printf("%-20s #%5d %9.9s %.55s\n", dateStr, item.Number, item.User.Login, item.Title)
		}
		fmt.Println()
	}
}
