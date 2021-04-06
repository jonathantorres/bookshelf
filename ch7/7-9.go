package main

import (
	"log"
	"net/http"
	"sort"
	"text/template"
	"time"
)

const html = `<html>
<head>
	<title>{{.PageTitle}}</title>
</head>
<body>
<style type="text/css">
table {
	border-collapse: collapse;
}
table, th, td {
	border: 1px solid black;
}
th, td {
	padding: 5px;
}
</style>
<p>{{.PageTitle}}</p>
<table>
	<thead>
		<tr>
			<th><a href="/?sort=Title">Title</a></th>
			<th><a href="/?sort=Artist">Artist</a></th>
			<th><a href="/?sort=Album">Album</a></th>
			<th><a href="/?sort=Year">Year</a></th>
			<th><a href="/?sort=Length">Length</a></th>
		</tr>
	</thead>
	<tbody>
		{{range .Tracks}}
			<tr>
				<td>{{.Title}}</td>
				<td>{{.Artist}}</td>
				<td>{{.Album}}</td>
				<td>{{.Year}}</td>
				<td>{{.Length}}</td>
			</tr>
		{{end}}
	</tbody>
</table>
</body>
</html>
`

type Track struct {
	Title  string
	Artist string
	Album  string
	Year   int
	Length time.Duration
}

type multiTier struct {
	s     []*Track
	tiers []string
}

func (s multiTier) Len() int           { return len(s.s) }
func (s multiTier) Swap(i, j int)      { s.s[i], s.s[j] = s.s[j], s.s[i] }
func (s multiTier) Less(i, j int) bool { return s.less(i, j) }
func (s multiTier) less(i, j int) bool {
	if len(s.tiers) == 0 {
		return s.s[i].Title < s.s[i].Title
	}
	iTrack := s.s[i]
	jTrack := s.s[j]
	for _, t := range s.tiers {
		if t == "Title" && iTrack.Title != jTrack.Title {
			return iTrack.Title < jTrack.Title
		}
		if t == "Artist" && iTrack.Artist != jTrack.Artist {
			return iTrack.Artist < jTrack.Artist
		}
		if t == "Album" && iTrack.Album != jTrack.Album {
			return iTrack.Album < jTrack.Album
		}
		if t == "Year" && iTrack.Year != jTrack.Year {
			return iTrack.Year < jTrack.Year
		}
		if t == "Length" && iTrack.Length != jTrack.Length {
			return iTrack.Length < jTrack.Length
		}
	}
	return false
}

func main() {
	http.HandleFunc("/", tracks)
	log.Fatal(http.ListenAndServe("localhost:8888", nil))
}

func tracks(w http.ResponseWriter, r *http.Request) {
	t, err := template.New("tracks").Parse(html)
	if err != nil {
		log.Fatalf("%s", err)
	}
	w.Header().Set("Content-Type", "text/html")
	var tracks = []*Track{
		{"Go", "Delilah", "From the Roots Up", 2012, length("3m38s")},
		{"Go", "Moby", "Moby", 1992, length("3m37s")},
		{"Go Ahead", "Alicia Keys", "As I Am", 2007, length("4m36s")},
		{"Ready 2 Go", "Martin Solveig", "Smash", 2011, length("4m24s")},
	}
	sortType := r.URL.Query().Get("sort")
	if sortType == "" {
		sortType = "Title"
	}
	m := multiTier{
		s:     tracks,
		tiers: []string{sortType},
	}
	sort.Sort(m)
	pageData := struct {
		PageTitle string
		Tracks    []*Track
	}{
		"List of Songs",
		tracks,
	}
	if err = t.Execute(w, pageData); err != nil {
		log.Fatalf("%s", err)
	}
}

func length(s string) time.Duration {
	d, err := time.ParseDuration(s)
	if err != nil {
		panic(s)
	}
	return d
}
