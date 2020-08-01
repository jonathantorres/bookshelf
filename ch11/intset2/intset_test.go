package intset

// Exercise 11.7

import (
	"testing"
	"math/rand"
)

const max = 32000

func addRandom(set *IntSet, n int) {
	for i := 0; i < n; i++ {
		set.Add(rand.Intn(max))
	}
}

func benchHas(b *testing.B, set *IntSet, n int) {
	addRandom(set, n)
	for i := 0; i < b.N; i++ {
		set.Has(rand.Intn(max))
	}
}

func benchAdd(b *testing.B, set *IntSet, n int) {
	for i := 0; i < b.N; i++ {
		for j := 0; j < n; j++ {
			set.Add(rand.Intn(max))
		}
		set.Clear()
	}
}

func randInts(n int) []int {
	ints := make([]int, n)
	for i := 0; i < n; i++ {
		ints[i] = rand.Intn(max)
	}
	return ints
}

func benchAddAll(b *testing.B, set *IntSet, batchSize int) {
	ints := randInts(batchSize)
	for i := 0; i < b.N; i++ {
		set.AddAll(ints...)
		set.Clear()
	}
}

func benchUnionWith(bm *testing.B, a, b *IntSet, n int) {
	addRandom(a, n)
	addRandom(b, n)
	for i := 0; i < bm.N; i++ {
		a.UnionWith(b)
	}
}

func benchString(b *testing.B, set *IntSet, n int) {
	addRandom(set, n)
	for i := 0; i < b.N; i++ {
		set.String()
	}
}

func NewIntSet() *IntSet {
	return &IntSet{}
}
func BenchmarkIntSetAdd1(b *testing.B) {
	benchAdd(b, NewIntSet(), 1)
}
func BenchmarkIntSetAdd10(b *testing.B) {
	benchAdd(b, NewIntSet(), 10)
}
func BenchmarkIntSetAdd100(b *testing.B) {
	benchAdd(b, NewIntSet(), 100)
}
func BenchmarkIntSetAdd1000(b *testing.B) {
	benchAdd(b, NewIntSet(), 1000)
}
func BenchmarkIntSetHas10(b *testing.B) {
	benchHas(b, NewIntSet(), 10)
}
func BenchmarkIntSetHas100(b *testing.B) {
	benchHas(b, NewIntSet(), 100)
}
func BenchmarkIntSetHas1000(b *testing.B) {
	benchHas(b, NewIntSet(), 1000)
}
func BenchmarkMapIntSetAddAll10(b *testing.B) {
	benchAddAll(b, NewIntSet(), 10)
}
func BenchmarkIntSetAddAll100(b *testing.B) {
	benchAddAll(b, NewIntSet(), 100)
}
func BenchmarkIntSetAddAll1000(b *testing.B) {
	benchAddAll(b, NewIntSet(), 1000)
}
func BenchmarkIntSetString10(b *testing.B) {
	benchString(b, NewIntSet(), 10)
}
func BenchmarkIntSetString100(b *testing.B) {
	benchString(b, NewIntSet(), 100)
}
func BenchmarkIntSetString1000(b *testing.B) {
	benchString(b, NewIntSet(), 1000)
}
func BenchmarkIntSetUnionWith10(b *testing.B) {
	benchUnionWith(b, NewIntSet(), NewIntSet(), 10)
}
func BenchmarkIntSetUnionWith100(b *testing.B) {
	benchUnionWith(b, NewIntSet(), NewIntSet(), 100)
}
func BenchmarkIntSetUnionWith1000(b *testing.B) {
	benchUnionWith(b, NewIntSet(), NewIntSet(), 1000)
}
