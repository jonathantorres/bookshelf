package main

// Exercise 4.11

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	// create issue: ismana create {user/repo} {issue title} {issue content}
	// read issue: ismana read {user/repo} {issue number}
	// update issue: ismana update {user/repo} {issue number} {issue title} {issue content}
	// close issue: ismana close {user/repo} {issue number}
	if len(os.Args) < 4 {
		printInfo()
		os.Exit(1)
	}
	switch os.Args[1] {
	case "create":
		createIssue(os.Args[2:])
	case "read":
		readIssue(os.Args[2:])
	case "update":
		updateIssue(os.Args[2:])
	case "close":
		closeIssue(os.Args[2:])
	case "help":
		printInfo()
		os.Exit(0)
	default:
		cmdNotSupported(os.Args[1])
	}
}

func createIssue(args []string) {
	if len(args) == 1 {
		fmt.Fprintf(os.Stderr, "A title for the issue is required")
		printInfo()
		os.Exit(1)
	}
	repo := args[0]
	title := args[1]
	var content string
	if len(args) >= 3 {
		content = args[2]
	}
	fmt.Println("repo", repo)
	fmt.Println("title", title)
	fmt.Println("content", content)
}

func readIssue(args []string) {
	if len(args) == 1 {
		fmt.Fprintf(os.Stderr, "A number for the issue is required")
		printInfo()
		os.Exit(1)
	}
	repo_user := args[0]
	number, err := strconv.Atoi(args[1])
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	issue, err := getIssue(repo_user, int64(number))
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	fmt.Println(issue.Title)
}

func updateIssue(args []string) {
	if len(args) <= 2 {
		fmt.Fprintf(os.Stderr, "A number and title for the issue is required")
		printInfo()
		os.Exit(1)
	}
}

func closeIssue(args []string) {
	if len(args) == 1 {
		fmt.Fprintf(os.Stderr, "A number for the issue is required")
		printInfo()
		os.Exit(1)
	}
}

func cmdNotSupported(cmd string) {
	fmt.Fprintf(os.Stderr, "command %s is not supported", cmd)
	printInfo()
	os.Exit(1)
}

func printInfo() {
	var info string = `usage: ismana [command] [values]
where [command] is one of: create, read, update or close
to create an issue: ismana create {user/repo} {issue title} {issue content}
to read an issue: ismana read {user/repo} {issue number}
to update an issue: ismana update {user/repo} {issue number} {issue title} {issue content}
to close an issue: ismana close {user/repo} {issue number}
`
	fmt.Println(info)
}
