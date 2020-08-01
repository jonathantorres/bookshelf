package popcount

// Exercise 11.6

import (
	"testing"
)

func bench(b *testing.B, f func(uint64) int) {
	for i := 0; i < b.N; i++ {
		f(uint64(i))
	}
}

func benchN(b *testing.B, n int, f func(uint64) int) {
	for i := 0; i < b.N; i++ {
		for j := 0; j < n; j++ {
			f(uint64(j))
		}
	}
}

func BenchmarkShift(b *testing.B) {
	bench(b, PopCountShift)
}

func BenchmarkRight(b *testing.B) {
	bench(b, PopCountRight)
}

func BenchmarkRight1(b *testing.B) {
	benchN(b, 1, PopCountRight)
}

func BenchmarkRight10(b *testing.B) {
	benchN(b, 10, PopCountRight)
}

func BenchmarkRight100(b *testing.B) {
	benchN(b, 100, PopCountRight)
}

func BenchmarkRight1000(b *testing.B) {
	benchN(b, 1000, PopCountRight)
}

func BenchmarkRight10000(b *testing.B) {
	benchN(b, 10000, PopCountRight)
}

func BenchmarkShift1(b *testing.B) {
	benchN(b, 1, PopCountShift)
}

func BenchmarkShift10(b *testing.B) {
	benchN(b, 10, PopCountShift)
}

func BenchmarkShift100(b *testing.B) {
	benchN(b, 100, PopCountShift)
}

func BenchmarkShift1000(b *testing.B) {
	benchN(b, 1000, PopCountShift)
}

func BenchmarkShift10000(b *testing.B) {
	benchN(b, 10000, PopCountShift)
}
