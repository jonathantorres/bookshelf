package main

import (
	"fmt"
	"os"
	"text/template"
	"time"
	"vamos/go_programming/ch4/github"
)

const templ = `{{.TotalCount}} issues:
{{range .Items}}-----------------------------
Number: {{.Number}}
User:   {{.User.Login}}
Title:  {{.Title | printf "%.64s"}}
Age:    {{.CreatedAt | daysAgo}} days
{{end}}`

var report = template.Must(template.New("issuelist").
	Funcs(template.FuncMap{"daysAgo": daysAgo}).
	Parse(templ))

func main() {
	result, err := github.SearchIssues(os.Args[1:])
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	if err := report.Execute(os.Stdout, result); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}

func daysAgo(t time.Time) int {
	return int(time.Since(t).Hours() / 24)
}
