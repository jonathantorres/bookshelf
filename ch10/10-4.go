package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"os/exec"
	"sort"
	"strings"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "usage: go run 10-4 [packages]\n")
		os.Exit(1)
	}
	pkgs := getDependants(getImportPaths(os.Args[1:]))
	sort.StringSlice(pkgs).Sort()
	for _, pkg := range pkgs {
		fmt.Println(pkg)
	}
}

func getImportPaths(pkgNames []string) []string {
	args := []string{"list", "-f={{.ImportPath}}"}
	for _, pkg := range pkgNames {
		args = append(args, pkg)
	}
	out, err := exec.Command("go", args...).Output()
	if err != nil {
		fmt.Fprintf(os.Stderr, "could not get packages: %s\n", err)
		os.Exit(1)
	}
	return strings.Fields(string(out))
}

func getDependants(packages []string) []string {
	targets := make(map[string]bool)
	for _, pkg := range packages {
		targets[pkg] = true
	}
	args := []string{"list", `-f={{.ImportPath}} {{join .Deps " "}}`, "..."}
	out, err := exec.Command("go", args...).Output()
	if err != nil {
		fmt.Fprintf(os.Stderr, "could not parse dependants: %s\n", err)
		os.Exit(1)
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
