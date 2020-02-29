package main

import (
	"fmt"
	"html/template"
	"os"
	"time"
	"vamos/go_programming/ch4/github"
)

const templ = `
<h1>{{.TotalCount}} issues</h1>
<table>
<tr style="text-align:left">
	<th>#</th>
	<th>State</th>
	<th>User</th>
	<th>Title</th>
</tr>
{{range .Items}}
<tr>
	<td><a href="{{.HTMLURL}}">{{.Number}}</td>
	<td>{{.State}}</td>
	<td><a href="{{.User.HTMLURL}}">{{.User.Login}}</td>
	<td><a href="{{.HTMLURL}}">{{.Title}}</td>
</tr>
{{end}}
</table>
`

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
