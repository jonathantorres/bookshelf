package main

// Exercise 10.4

import (
	"bufio"
	"bytes"
	"fmt"
	"log"
	"os"
	"os/exec"
	"sort"
	"strings"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: depends [packages]\n")
		os.Exit(1)
	}
	pkgs := dependants(packages(os.Args[1:]))
	sort.StringSlice(pkgs).Sort()
	for _, pkg := range pkgs {
		fmt.Println(pkg)
	}
}

func logError(context string, err error) {
	ee, ok := err.(*exec.ExitError)
	if !ok {
		log.Fatalf("%s: %s", context, err)
	}
	log.Printf("%s: %s", context, err)
	os.Stderr.Write(ee.Stderr)
	os.Exit(1)
}

func packages(patterns []string) []string {
	args := []string{"list", "-f={{.ImportPath}}"}
	for _, pkg := range patterns {
		args = append(args, pkg)
	}
	out, err := exec.Command("go", args...).Output()
	if err != nil {
		logError("resolve packages", err)
	}
	return strings.Fields(string(out))
}

func dependants(packageNames []string) []string {
	targets := make(map[string]bool)
	for _, pkg := range packageNames {
		targets[pkg] = true
	}

	args := []string{"list", `-f={{.ImportPath}} {{join .Deps " "}}`, "..."}
	out, err := exec.Command("go", args...).Output()
	if err != nil {
		logError("find dependants", err)
	}
	var pkgs []string
	s := bufio.NewScanner(bytes.NewReader(out))
	for s.Scan() {
		fields := strings.Fields(s.Text())
		pkg := fields[0]
		deps := fields[1:]
		for _, dep := range deps {
			if targets[dep] {
				pkgs = append(pkgs, pkg)
				break
			}
		}
	}
	return pkgs
}
