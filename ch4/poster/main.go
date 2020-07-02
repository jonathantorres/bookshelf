package main

// Exercise 4.13

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
	"strings"
)

type Results struct {
	Search []Movie `json:"Search"`
}

type Movie struct {
	Title  string `json:"Title"`
	Year   string `json:"Year"`
	ImdbId string `json:"imdbID"`
	Type   string `json:"Type"`
	Poster string `json:"Poster"`
}

const apiKey = "YOURKEY" // replace with your API key
const omdbUrl = "http://www.omdbapi.com/?apikey=" + apiKey + "&type=movie"

func main() {
	if len(os.Args) == 1 {
		fmt.Fprintf(os.Stderr, "usage: poster [search term]\n")
		os.Exit(1)
	}
	query := strings.Trim(os.Args[1], " ")
	fmt.Printf("Downloading poster(s) for %s\n", query)
	url := omdbUrl + "&s=" + query
	resp, err := http.Get(url)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Problem with the request: %s\n", err)
		os.Exit(1)
	}
	defer resp.Body.Close()
	if resp.StatusCode != 200 {
		fmt.Fprintf(os.Stderr, "There was a problem with the response: %s\n", err)
		os.Exit(1)
	}
	var results Results
	if err = json.NewDecoder(resp.Body).Decode(&results); err != nil {
		fmt.Fprintf(os.Stderr, "There was a problem decoding the JSON: %s\n", err)
		os.Exit(1)
	}
	if len(results.Search) == 0 {
		fmt.Println("No results")
		os.Exit(0)
	}
	for _, movie := range results.Search {
		resp, err = http.Get(movie.Poster)
		if err != nil {
			fmt.Fprintf(os.Stderr, "Could not download poster for %s: %s\n", movie.Title, err)
			continue
		}
		imgData, err := ioutil.ReadAll(resp.Body)
		if err != nil {
			fmt.Fprintf(os.Stderr, "Could not read image data from poster for %s: %s\n", movie.Title, err)
			continue
		}
		resp.Body.Close()
		filename := "poster_" + movie.ImdbId + ".jpg"
		if err = ioutil.WriteFile(filename, imgData, 0644); err != nil {
			fmt.Fprintf(os.Stderr, "Could not save poster image for %s: %s\n", movie.Title, err)
			continue
		}
		var wdir string
		if wdir, err = os.Getwd(); err != nil {
			wdir = "N/A"
		}
		fmt.Printf("Poster saved for %s at %s/%s\n", movie.Title, wdir, filename)
	}
}
