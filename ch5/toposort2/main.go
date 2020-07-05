package main

// Exercise 5.10

import (
	"fmt"
)

var prereqs = map[string]map[int]string{
	"algorithms": map[int]string{
		1: "data structures",
	},
	"calculus": map[int]string{
		1: "linear algebra",
	},
	"compilers": map[int]string{
		1: "data structures",
		2: "formal languages",
		3: "computer organization",
	},
	"data structures": map[int]string{
		1: "discrete math",
	},
	"databases": map[int]string{
		1: "data structures",
	},
	"discrete math": map[int]string{
		1: "intro to programming",
	},
	"formal languages": map[int]string{
		1: "discrete math",
	},
	"networks": map[int]string{
		1: "operating systems",
	},
	"operating systems": map[int]string{
		1: "data structures",
		2: "computer organization",
	},
	"programming languages": map[int]string{
		1: "data structures",
		2: "computer organization",
	},
}

func main() {
	for i, course := range topoSort(prereqs) {
		fmt.Printf("%d:\t%s\n", i+1, course)
	}
}

func topoSort(m map[string]map[int]string) map[int]string {
	order := make(map[int]string)
	seen := make(map[string]bool)
	var visitAll func(items map[int]string)

	visitAll = func(items map[int]string) {
		for i, item := range items {
			if !seen[item] {
				seen[item] = true
				visitAll(m[item])
				order[i] = item
			}
		}
	}

	var i int
	keys := make(map[int]string)
	for k, v := range m {
		for _, class := range v {
			if !valInMap(keys, class) {
				keys[i] = class
				i++
			}
			if !valInMap(keys, k) {
				keys[i] = k
				i++
			}
		}
	}
	visitAll(keys)
	return order
}

func valInMap(m map[int]string, s string) bool {
	var inMap = false
	for _, v := range m {
		if v == s {
			inMap = true
			break
		}
	}
	return inMap
}
