package main

import "fmt"

func main() {
	elements := map[string]map[string]string {
		"H": map[string]string {
			"name": "Hydrogen",
			"state": "Gas",
		},
		"He": map[string]string {
			"name": "Hellium",
			"state": "Gas",
		},
		"Li": map[string]string {
			"name": "Lithium",
			"state": "Solid",
		},
		"Be": map[string]string {
			"name": "Beryllium",
			"state": "Solid",
		},
		"B": map[string]string {
			"name": "Boron",
			"state": "Solid",
		},
		"C": map[string]string {
			"name": "Carbon",
			"state": "Solid",
		},
		"N": map[string]string {
			"name": "Nitrogen",
			"state": "Gas",
		},
		"O": map[string]string {
			"name": "Oxygen",
			"state": "Gas",
		},
		"F": map[string]string {
			"name": "Fluorine",
			"state": "Gas",
		},
		"Ne": map[string]string {
			"name": "Neon",
			"state": "Gas",
		},
	}
	if elem, ok := elements["H"]; ok {
		fmt.Println(elem["name"], elem["state"])
	}
}
