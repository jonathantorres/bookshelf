package main

import "fmt"

func main() {
	elements := map[string]string{
		"He": "Hellium",
		"Li": "Lithium",
		"Be": "Beryllium",
		"B": "Boron",
		"C": "Carbon",
		"N": "Nitrogen",
		"O": "Oxygen",
		"F": "Fluorine",
		"Ne": "Neon",
	}
	if name, ok := elements["F"]; ok {
		fmt.Println(name)
	}
	fmt.Println(elements)
}
