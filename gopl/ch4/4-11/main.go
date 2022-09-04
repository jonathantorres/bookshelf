package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"strconv"
	"strings"
)

func main() {
	if len(os.Args) <= 2 {
		printInfo()
		os.Exit(1)
	}
	switch os.Args[1] {
	case "create":
		createIssue(os.Args[2])
	case "read":
		readIssue(os.Args[2], os.Args[3])
	case "update":
		updateIssue(os.Args[2], os.Args[3])
	case "close":
		closeIssue(os.Args[2], os.Args[3])
	case "help":
		printInfo()
		os.Exit(0)
	default:
		cmdNotSupported(os.Args[1])
	}
}

func createIssue(repo string) {
	title, content := getTitleAndContent()
	_, err := createNewIssue(repo, title, content)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	fmt.Println("Issue created!")
}

func readIssue(repo string, num string) {
	number, err := strconv.Atoi(num)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	issue, err := getIssue(repo, int64(number))
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	fmt.Fprintf(os.Stdout, "#%-5d %-30s %s\n%s\n", issue.Number, repo, issue.Title, issue.Body)
}

func updateIssue(repo string, num string) {
	number, err := strconv.Atoi(num)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	title, content := getTitleAndContent()
	_, err = updateExistingIssue(repo, int64(number), title, content)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	fmt.Println("Issue has been updated")
}

func closeIssue(repo string, num string) {
	number, err := strconv.Atoi(num)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	_, err = closeExistingIssue(repo, int64(number))
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	fmt.Println("Issue has been closed")
}

func getTitleAndContent() (string, string) {
	title, content := "", ""
	tmpFile := "tmp_msg"
	f, err := os.Create(tmpFile)
	if err != nil {
		fmt.Fprintf(os.Stderr, "create error: %s\n", err)
		os.Exit(1)
	}
	defer f.Close()
	var msg = `# Type the title of your issue on the line below these comments,
# any line after it it will be used as the body for it.
# Any line that starts with "#" is ignored.

`
	_, err = f.Write([]byte(msg))
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	cmd := exec.Command("vim", tmpFile)
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	err = cmd.Run()
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	fContents, err := os.Open(tmpFile)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	defer fContents.Close()
	s := bufio.NewScanner(fContents)
	var wroteTitle bool
	for s.Scan() {
		l := s.Text()
		if strings.HasPrefix(l, "#") {
			continue // ignore comments
		}
		if !wroteTitle {
			title += l
			wroteTitle = true
			continue
		}
		content += l
		content += string('\n')
	}
	if err = s.Err(); err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	os.Remove(tmpFile)
	return title, content
}

func cmdNotSupported(cmd string) {
	fmt.Fprintf(os.Stderr, "command %s is not supported", cmd)
	printInfo()
	os.Exit(1)
}

func printInfo() {
	var info string = `usage: 4-11 [command] [values]
where [command] is one of: create, read, update or close
to create an issue: 4-11 create {user/repo}
to read an issue: 4-11 read {user/repo} {issue number}
to update an issue: 4-11 update {user/repo} {issue number}
to close an issue: 4-11 close {user/repo} {issue number}
`
	fmt.Fprintf(os.Stderr, info)
}
