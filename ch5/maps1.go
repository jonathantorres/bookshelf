package main

import (
	"fmt"
)

func main() {
	// creates an empty map
	// a map is like an associative array
	// this map uses strings as keys and integers as a value
	var x = map[string]int

	// make sure to initialize the map
	// with "make()" before you use it
	y := make(map[string]int)
	y["key"] = 10
	y["foo"] = 11
	y["bar"] = 12

	// removing items from a map
	delete(y, "bar")

	elements := make(map[string]string)
	elements["H"] = "Hydrogen"
	elements["He"] = "Helium"
	elements["Li"] = "Lithium"
	elements["Be"] = "Beryllium"
	elements["B"] = "Boron"
	elements["C"] = "Carbon"
	elements["N"] = "Nitrogen"

	// attempting to get a value from a map
	// this one doesn't exist, so the block doesn't execute
	if el_name, el_found := elements["U"]; el_found {
		fmt.Println(el_name, el_found)
	}

	// a shorter way to create maps
	players := map[int]string{
		1: "One",
		2: "Two",
		3: "Three",
		4: "Four",
		5: "Five",
	}

	// a map used to store general information
	complex_elems := map[string]map[string]string{
		"H": map[string]string{
			"name":  "Hydrogen",
			"state": "gas",
		},
		"He": map[string]string{
			"name":  "Helium",
			"state": "gas",
		},
		"Li": map[string]string{
			"name":  "Lithium",
			"state": "solid",
		},
		"Be": map[string]string{
			"name":  "Beryllium",
			"state": "solid",
		},
		"B": map[string]string{
			"name":  "Boron",
			"state": "solid",
		},
		"C": map[string]string{
			"name":  "Carbon",
			"state": "solid",
		},
	}

	// checking if the element with key "Li" exists,
	// if it does, print it's "name" and "state"
	if elem, ok := complex_elems["Li"]; ok {
		fmt.Println(elem["name"], elem["state"])
	}

	fmt.Println(x)
	fmt.Println(y)
	fmt.Println(elements)
	fmt.Println(players)
}
