package main

import (
	"fmt"
)

var names map[string]string

var formulas = make(map[string]string)

var countries map[string]string = map[string]string{
	"US": "United States",
}

var moreCountries = map[string]string{
	"US": "United States",
}

func main() {
	fmt.Println("aight")
	fmt.Println(countries)

	for k, v := range moreCountries {
		fmt.Println("Abbr: " + k + " Country: " + v)
	}

	if _, ok := moreCountries["PR"]; ok {
		fmt.Println("it's there")
	} else {
		fmt.Println("nope")
	}
}
