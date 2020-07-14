package main

// Exercise 7.9

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
	"sort"
	"strings"
	"time"
)

type TrackManagement struct {
	PageTitle string
	Tracks    []*Track
	Cols      []string
	OrderBy   string
}

var tracks = []*Track{
	{"Go", "Delilah", "From the Roots Up", 2012, length("3m38s")},
	{"Go", "Moby", "Moby", 1992, length("3m37s")},
	{"Go Ahead", "Alicia Keys", "As I Am", 2007, length("4m36s")},
	{"Ready 2 Go", "Martin Solveig", "Smash", 2011, length("4m24s")},
}

var templ = `
<html>
	<head>
		<title>{{.PageTitle}}</title>
		<style>
		table {
			font-family: arial, sans-serif;
			border-collapse: collapse;
			width: 800px;
		}
		td, th {
			border: 1px solid #dddddd;
			text-align: left;
			padding: 8px;
		}
		</style>
	</head>
	<body>
		<h1>{{.PageTitle}}</h1>
		<table>
			<thead>
				<tr>
					{{ range $i, $col := .Cols }}
					<th>
						<a href="/?sort_by={{ $col }}&order_by={{ $.OrderBy }}">{{ $col | capitalize }}</a>
					</th>
					{{ end }}
				</tr>
			</thead>
			<tbody>
				{{ range $i, $track := .Tracks }}
				<tr>
					<td>{{ $track.Title }}</td>
					<td>{{ $track.Artist }}</td>
					<td>{{ $track.Album }}</td>
					<td>{{ $track.Year }}</td>
					<td>{{ $track.Length }}</td>
				</tr>
				{{ end }}
			</tbody>
		</table>
	</body>
</html>
`

func main() {
	http.HandleFunc("/", handleTracks)
	log.Fatal(http.ListenAndServe(":9999", nil))
}

func handleTracks(w http.ResponseWriter, r *http.Request) {
	w.Header().Add("Content-Type", "text/html")
	tracksTempl, err := template.New("tracks").
		Funcs(template.FuncMap{"capitalize": capitalize}).
		Parse(templ)
	if err != nil {
		fmt.Fprintf(w, "Error, parsing the template %s", err)
		return
	}
	sortBy := r.URL.Query().Get("sort_by")
	orderBy := r.URL.Query().Get("order_by")
	if orderBy == "" {
		orderBy = "asc"
	}
	if sortBy != "" {
		handleSorting(sortBy, orderBy)
	} else {
		sort.Sort(byArtist(tracks))
	}
	if orderBy == "asc" {
		orderBy = "desc"
	} else {
		orderBy = "asc"
	}
	var cols = []string{"title", "artist", "album", "year", "length"}
	var tracksManagement = TrackManagement{
		PageTitle: "These are the tracks",
		Tracks:    tracks,
		Cols:      cols,
		OrderBy:   orderBy,
	}
	if err := tracksTempl.Execute(w, tracksManagement); err != nil {
		fmt.Fprintf(w, "Error, executing the template %s", err)
	}
}

func handleSorting(sortType, orderBy string) {
	var sortFunc sort.Interface
	switch sortType {
	case "title":
		sortFunc = byTitle(tracks)
	case "artist":
		sortFunc = byArtist(tracks)
	case "album":
		sortFunc = byAlbum(tracks)
	case "year":
		sortFunc = byYear(tracks)
	case "length":
		sortFunc = byLength(tracks)
	default:
		sortFunc = byArtist(tracks)
	}
	if orderBy == "asc" {
		sort.Sort(sortFunc)
	} else {
		sort.Sort(sort.Reverse(sortFunc))
	}
}

func capitalize(s string) string {
	return strings.Title(s)
}

func length(s string) time.Duration {
	d, err := time.ParseDuration(s)
	if err != nil {
		panic(s)
	}
	return d
}
