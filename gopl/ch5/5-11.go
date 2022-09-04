package main

import (
	"fmt"
	"sort"
)

// prereqs maps computer science courses to their prerequisites.
var prereqs = map[string][]string{
	"algorithms": {"data structures"},
	"calculus":   {"linear algebra"},
	"compilers": {
		"data structures",
		"formal languages",
		"computer organization",
	},
	"linear algebra":        {"calculus"},
	"data structures":       {"discrete math"},
	"databases":             {"data structures"},
	"discrete math":         {"intro to programming"},
	"formal languages":      {"discrete math"},
	"networks":              {"operating systems"},
	"operating systems":     {"data structures", "computer organization"},
	"programming languages": {"data structures", "computer organization"},
}

func main() {
	courses, cycles := topoSort(prereqs)
	for i, course := range courses {
		fmt.Printf("%d:\t%s\n", i+1, course)
	}
	if cycles != nil {
		fmt.Printf("\ncycles:\n")
		for c, pres := range cycles {
			fmt.Printf("%s:\t%v\n", c, pres)
		}
	}
}

func cycle(item string, items []string) bool {
	for _, i := range items {
		if pres, ok := prereqs[i]; ok {
			for _, p := range pres {
				if item == p {
					return true
				}
			}
		}
	}
	return false
}

func topoSort(m map[string][]string) ([]string, map[string][]string) {
	var order []string
	var cycles map[string][]string
	seen := make(map[string]bool)
	var visitAll func(items []string)

	visitAll = func(items []string) {
		for _, item := range items {
			if !seen[item] {
				seen[item] = true
				if cycle(item, m[item]) {
					if cycles == nil {
						cycles = make(map[string][]string)
					}
					cycles[item] = m[item]
				}
				visitAll(m[item])
				order = append(order, item)
			}
		}
	}

	var keys []string
	for key := range m {
		keys = append(keys, key)
	}

	sort.Strings(keys)
	visitAll(keys)
	return order, cycles
}
