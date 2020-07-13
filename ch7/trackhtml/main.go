package main

// Exercise 7.9

import (
	"fmt"
	"net/http"
	"os"
	// "sort"
	"log"
	"text/tabwriter"
	"time"
)

var tracks = []*Track{
	{"Go", "Delilah", "From the Roots Up", 2012, length("3m38s")},
	{"Go", "Moby", "Moby", 1992, length("3m37s")},
	{"Go Ahead", "Alicia Keys", "As I Am", 2007, length("4m36s")},
	{"Ready 2 Go", "Martin Solveig", "Smash", 2011, length("4m24s")},
}

var tmp = `
<html>
	<head>
		<title>tracks</title>
	</head>
	<body>
		<h1>Song Tracks</h1>
		<table>
			<thead>
				<tr>
					<th>Title</th>
					<th>Artist</th>
					<th>Album</th>
					<th>Year</th>
					<th>Length</th>
				</tr>
			</thead>
			<tbody>
				<tr>
					<td>One</td>
					<td>Two</td>
					<td>Three</td>
					<td>Four</td>
					<td>Five</td>
				</tr>
			</tbody>
		</table>
	</body>
</html>
`

func main() {
	http.HandleFunc("/", handleTracks)
	log.Fatal(http.ListenAndServe(":9999", nil))
	// sort.Sort(byArtist(tracks))
	// printTracks(tracks)
}

func handleTracks(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "hola!")
}

func printTracks(tracks []*Track) {
	const format = "%v\t%v\t%v\t%v\t%v\t\n"
	tw := new(tabwriter.Writer).Init(os.Stdout, 0, 8, 2, ' ', 0)
	fmt.Fprintf(tw, format, "Title", "Artist", "Album", "Year", "Length")
	fmt.Fprintf(tw, format, "-----", "-----", "-----", "-----", "-----")
	for _, t := range tracks {
		fmt.Fprintf(tw, format, t.Title, t.Artist, t.Album, t.Year, t.Length)
	}
	tw.Flush()
}

func length(s string) time.Duration {
	d, err := time.ParseDuration(s)
	if err != nil {
		panic(s)
	}
	return d
}
