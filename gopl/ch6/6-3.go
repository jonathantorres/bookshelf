package main

import (
	"bytes"
	"fmt"
)

func main() {
	s := &IntSet{}
	s.Add(1)
	s.Add(2)
	s.Add(3)

	t := &IntSet{}
	t.Add(3)
	t.Add(4)
	s.SymmetricDifference(t)
	fmt.Println("s:", s)
}

// An IntSet is a set of small non-negative integers.
// Its zero value represents the empty set.
type IntSet struct {
	words []uint64
}

// Has reports whether the set contains the non-negative value x.
func (s *IntSet) Has(x int) bool {
	word, bit := x/64, uint(x%64)
	return word < len(s.words) && s.words[word]&(1<<bit) != 0
}

// Add adds the non-negative value x to the set.
func (s *IntSet) Add(x int) {
	word, bit := x/64, uint(x%64)
	for word >= len(s.words) {
		s.words = append(s.words, 0)
	}
	s.words[word] |= 1 << bit
}

// UnionWith sets s to the union of s and t.
func (s *IntSet) UnionWith(t *IntSet) {
	for i, tword := range t.words {
		if i < len(s.words) {
			s.words[i] |= tword
		} else {
			s.words = append(s.words, tword)
		}
	}
}

// IntersectWith sets s to the elements that are in both s and t
func (s *IntSet) IntersectWith(t *IntSet) {
	for i, w := range t.words {
		if i < len(s.words) {
			s.words[i] &= w
		} else {
			s.words = append(s.words, w)
		}
	}
}

// DifferenceWith removes the elements from s that are in t
func (s *IntSet) DifferenceWith(t *IntSet) {
	for i, w := range t.words {
		if i < len(s.words) {
			s.words[i] &= ^w
		} else {
			s.words = append(s.words, 0)
		}
	}
}

// SymmetricDifference merges s and t and then removes elements from s that are in both s and t
func (s *IntSet) SymmetricDifference(t *IntSet) {
	for i, w := range t.words {
		if i < len(s.words) {
			s.words[i] ^= w
		} else {
			s.words = append(s.words, 0)
		}
	}
}

// String returns the set as a string of the form "{1 2 3}".
func (s *IntSet) String() string {
	var buf bytes.Buffer
	buf.WriteByte('{')
	for i, word := range s.words {
		if word == 0 {
			continue
		}
		for j := 0; j < 64; j++ {
			if word&(1<<uint(j)) != 0 {
				if buf.Len() > len("{") {
					buf.WriteByte(' ')
				}
				fmt.Fprintf(&buf, "%d", 64*i+j)
			}
		}
	}
	buf.WriteByte('}')
	return buf.String()
}
