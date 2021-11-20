package main

import (
	"fmt"
	"os"
	"strings"
)

const hashSize = 101

type nlist struct {
	next *nlist
	name string
	defn string
}

var hashtab []*nlist

func main() {
	hashtab = make([]*nlist, hashSize)
	lu := install("Jonathan", "def")
	if lu == nil {
		fmt.Println("Error!")
		os.Exit(1)
	}
	var r *nlist
	if r = lookup("Jonathan"); r == nil {
		fmt.Println("Error with lookup")
		os.Exit(1)
	}
	fmt.Println(r.name, r.defn)
	undef("Jonathan")
	if r = lookup("Jonathan"); r != nil {
		fmt.Println("Error with lookup, Jonathan should not be there")
		os.Exit(1)
	}
}

func lookup(s string) *nlist {
	var np *nlist
	for np = hashtab[hash(s)]; np != nil; np = np.next {
		if strings.Compare(s, np.name) == 0 {
			return np
		}
	}
	return nil
}

func install(name string, defn string) *nlist {
	var np *nlist
	var hashval uint
	np = lookup(name)
	if np == nil {
		np = &nlist{
			name: name,
		}
		hashval = hash(name)
		np.next = hashtab[hashval]
		hashtab[hashval] = np
	} else {
		np.defn = ""
	}
	np.defn = defn
	return np
}

func undef(s string) {
	var np1, np2 *nlist
	hashval := hash(s)
	for np1, np2 = hashtab[hashval], nil; np1 != nil; np2, np1 = np1, np1.next {
		if strings.Compare(s, np1.name) == 0 {
			if np2 == nil {
				hashtab[hashval] = np1.next
			} else {
				np2.next = np1.next
			}
			return
		}
	}
}

func hash(s string) uint {
	var hashval uint
	for _, c := range s {
		hashval = uint(int(c) + 31*int(hashval))
	}
	return hashval % hashSize
}
