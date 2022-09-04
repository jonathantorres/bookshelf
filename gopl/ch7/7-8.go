package main

import (
	"fmt"
	"os"
	"sort"
	"text/tabwriter"
	"time"
)

func main() {
	var tracks = []*Track{
		{"Go", "Delilah", "From the Roots Up", 2012, length("3m38s")},
		{"Go", "Moby", "Moby", 1992, length("3m37s")},
		{"Go Ahead", "Alicia Keys", "As I Am", 2007, length("4m36s")},
		{"Ready 2 Go", "Martin Solveig", "Smash", 2011, length("4m24s")},
	}
	printTracks(tracks)
	m := multiTier{
		s:     tracks,
		tiers: []string{"Title", "Year"},
	}
	sort.Sort(m)
	printTracks(tracks)
}

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

func printTracks(tracks []*Track) {
	const format = "%v\t%v\t%v\t%v\t%v\t\n"
	tw := new(tabwriter.Writer).Init(os.Stdout, 0, 8, 2, ' ', 0)
	fmt.Fprintf(tw, format, "Title", "Artist", "Album", "Year", "Length")
	fmt.Fprintf(tw, format, "-----", "-----", "-----", "-----", "-----")
	for _, t := range tracks {
		fmt.Fprintf(tw, format, t.Title, t.Artist, t.Album, t.Year, t.Length)
	}
	fmt.Fprintf(tw, "\n")
	tw.Flush()
}

func length(s string) time.Duration {
	d, err := time.ParseDuration(s)
	if err != nil {
		panic(s)
	}
	return d
}
