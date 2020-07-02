package main

// Exercise 4.14

import (
	"fmt"
	"github.com/jonathantorres/gopl/ch4/github"
	"html/template"
	"log"
	"net/http"
	"os"
	"time"
)

const templ = `
<h1>{{.TotalCount}} issues</h1>
<table>
<tr style="text-align:left">
	<th>#</th>
	<th>State</th>
	<th>User</th>
	<th>MileStone</th>
	<th>Title</th>
</tr>
{{range .Items}}
<tr>
	<td><a href="{{.HTMLURL}}">{{.Number}}</td>
	<td>{{.State}}</td>
	<td><a href="{{.User.HTMLURL}}">{{.User.Login}}</td>
	{{if .Milestone}}
		<td><a href="{{.Milestone.HTMLURL}}">{{.Milestone.Title}}</td>
	{{else}}
		<td>N/A</td>
	{{end}}
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
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		r.Header.Add("Content-Type", "text/html")
		if err := report.Execute(w, result); err != nil {
			fmt.Fprintf(w, "<h1>%s</h1>", err)
		}
	})
	log.Fatal(http.ListenAndServe(":9999", nil))
}

func daysAgo(t time.Time) int {
	return int(time.Since(t).Hours() / 24)
}
