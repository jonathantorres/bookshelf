package main

// Exercise 4.11

import (
	"fmt"
	"os"
)

func main() {
	// create issue: ismana create {repo} {issue title} {issue content}
	// read issue: ismana read {repo} {issue number}
	// update issue: ismana update {repo} {issue title} {issue content}
	// close issue: ismana close {repo} {issue number}
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

}

func readIssue(args []string) {

}

func updateIssue(args []string) {

}

func closeIssue(args []string) {

}

func cmdNotSupported(cmd string) {
	fmt.Fprintf(os.Stderr, "command %s is not supported", cmd)
	printInfo()
	os.Exit(1)
}

func printInfo() {
	var info string = `usage: ismana [command] [values]
where [command] is one of: create, read, update or close
to create an issue: ismana create {repo} {issue title} {issue content}
to read an issue: ismana read {repo} {issue number}
to update an issue: ismana update {repo} {issue number} {issue title} {issue content}
to close an issue: ismana close {repo} {issue number}
`
	fmt.Println(info)
}
