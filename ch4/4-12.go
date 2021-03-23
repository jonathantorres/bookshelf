package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
	"strconv"
	"strings"
)

const amountOfComics = 1000

type Comic struct {
	Num        int32  `json:"num"`
	Day        string `json:"day"`
	Year       string `json:"year"`
	Month      string `json:"month"`
	News       string `json:"news"`
	Title      string `json:"title"`
	Transcript string `json:"transcript"`
	Alt        string `json:"alt"`
	Image      string `json:"img"`
	Link       string `json:"link"`
}

func main() {
	if len(os.Args) <= 1 {
		printInfo()
		os.Exit(1)
	}
	for _, cmd := range os.Args[1:] {
		switch cmd {
		case "build":
			buildIndex()
		case "search":
			if len(os.Args) == 2 {
				fmt.Fprintf(os.Stderr, "A search keyword is required\n")
				printInfo()
				os.Exit(1)
			}
			searchComic(os.Args[2:])
		}
	}
}

func buildIndex() {
	fmt.Print("Building index...")
	comics := make([]*Comic, 0)
	for i := 1; i <= amountOfComics; i++ {
		resp, err := http.Get("https://xkcd.com/" + strconv.Itoa(i) + "/info.0.json")
		if err != nil {
			fmt.Fprintf(os.Stderr, "failed! %s\n", err)
			continue
		}
		if resp.StatusCode != 200 {
			fmt.Fprintf(os.Stderr, "failed! Problem with the request: %s\n", resp.Status)
			continue
		}
		comic := Comic{}
		err = json.NewDecoder(resp.Body).Decode(&comic)
		if err != nil {
			fmt.Fprintf(os.Stderr, "failed! Problem encoding response body: %s\n", err)
			continue
		}
		comics = append(comics, &comic)
		resp.Body.Close()
	}
	jsonStr, err := json.Marshal(comics)
	if err != nil {
		fmt.Fprintf(os.Stderr, "failed! Error marshaling data: %s", err)
		os.Exit(1)
	}
	if err = ioutil.WriteFile("xkcd.txt", jsonStr, 0644); err != nil {
		fmt.Fprintf(os.Stderr, "failed! Error saving offline data: %s", err)
		os.Exit(1)
	}
	fmt.Print("done!\n")
}

func searchComic(keywords []string) {
	contents, err := ioutil.ReadFile("xkcd.txt")
	if err != nil {
		fmt.Fprintf(os.Stderr, "There was a problem reading the file: %s", err)
		os.Exit(1)
	}
	var comics []Comic
	if err = json.Unmarshal(contents, &comics); err != nil {
		fmt.Fprintf(os.Stderr, "There was a problem unmarshalling contents: %s", err)
		os.Exit(1)
	}
	var results []Comic
	for _, comic := range comics {
		for _, keyword := range keywords {
			if strings.Index(comic.Title, keyword) != -1 || strings.Index(comic.Transcript, keyword) != -1 {
				results = append(results, comic)
			}
		}
	}
	if len(results) > 0 {
		for _, result := range results {
			fmt.Printf("#%d %s %s\n", result.Num, result.Title, result.Link)
		}
		return
	}
	fmt.Println("No results")
}

func printInfo() {
	usage := `usage: xkcd [command] [options]
where [command] is either build or search
xkcd build: To build the index
xkcd search [keyword] To search for a comic with the keyword
`
	fmt.Fprintf(os.Stderr, usage)
}
