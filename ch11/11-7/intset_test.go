package intset

import (
	"math/rand"
	"testing"
	"time"
)

func BenchmarkHas(b *testing.B) {
	rand.Seed(time.Now().UnixNano())
	s := &IntSet{}
	s.Add(rand.Intn(1000000))
	s.Add(rand.Intn(1000000))
	s.Add(rand.Intn(1000000))
	for i := -0; i < b.N; i++ {
		s.Has(rand.Intn(1000000))
	}
}

func BenchmarkLen(b *testing.B) {
	rand.Seed(time.Now().UnixNano())
	s := &IntSet{}
	s.Add(rand.Intn(1000000))
	s.Add(rand.Intn(1000000))
	s.Add(rand.Intn(1000000))
	for i := -0; i < b.N; i++ {
		s.Len()
	}
}

func BenchmarkAdd(b *testing.B) {
	rand.Seed(time.Now().UnixNano())
	s := &IntSet{}
	for i := -0; i < b.N; i++ {
		s.Add(rand.Intn(1000000))
	}
}

func BenchmarkUnionWith(b *testing.B) {
	rand.Seed(time.Now().UnixNano())
	s := &IntSet{}
	s.Add(rand.Intn(1000000))
	s.Add(rand.Intn(1000000))
	s.Add(rand.Intn(1000000))
	s2 := &IntSet{}
	s2.Add(rand.Intn(1000000))
	s2.Add(rand.Intn(1000000))

	for i := -0; i < b.N; i++ {
		s.UnionWith(s2)
	}
}
