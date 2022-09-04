package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"sync"
	"time"
)

var vFlag = flag.Bool("v", false, "show verbose progress messages")

type rootTotal struct {
	root   string
	nfiles int64
	nbytes int64
}

func main() {
	flag.Parse()

	// Determine the initial directories.
	roots := flag.Args()
	if len(roots) == 0 {
		roots = []string{"."}
	}

	var totals []*rootTotal
	for _, r := range roots {
		totals = append(totals, &rootTotal{r, 0, 0})
	}

	// Traverse each root of the file tree in parallel.
	fileTotals := make(chan rootTotal)
	var n sync.WaitGroup
	for _, root := range roots {
		n.Add(1)
		go walkDir(root, root, &n, fileTotals)
	}
	go func() {
		n.Wait()
		close(fileTotals)
	}()

	// Print the results periodically.
	var tick <-chan time.Time
	if *vFlag {
		tick = time.Tick(100 * time.Millisecond)
	}
loop:
	for {
		select {
		case size, ok := <-fileTotals:
			if !ok {
				break loop // fileTotals was closed
			}
			addTotals(totals, size)
		case <-tick:
			printDiskUsage(totals)
		}
	}

	printDiskUsage(totals) // final totals
}

func addTotals(totals []*rootTotal, total rootTotal) {
	for i, t := range totals {
		if t.root == total.root {
			totals[i].nbytes += total.nbytes
			totals[i].nfiles += total.nfiles
		}
	}
}

func printDiskUsage(totals []*rootTotal) {
	for _, t := range totals {
		fmt.Printf("%s:\t%d files %.1f GB\n", t.root, t.nfiles, float64(t.nbytes)/1e9)
	}
}

func walkDir(dir string, curRoot string, n *sync.WaitGroup, fileTotals chan<- rootTotal) {
	defer n.Done()
	for _, entry := range dirents(dir) {
		if entry.IsDir() {
			n.Add(1)
			subdir := filepath.Join(dir, entry.Name())
			go walkDir(subdir, curRoot, n, fileTotals)
		} else {
			fileTotals <- rootTotal{curRoot, 1, entry.Size()}
		}
	}
}

var sema = make(chan struct{}, 20)

func dirents(dir string) []os.FileInfo {
	sema <- struct{}{}        // acquire token
	defer func() { <-sema }() // release token
	entries, err := ioutil.ReadDir(dir)
	if err != nil {
		fmt.Fprintf(os.Stderr, "du: %v\n", err)
		return nil
	}
	return entries
}
