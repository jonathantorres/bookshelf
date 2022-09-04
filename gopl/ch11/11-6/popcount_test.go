package popcount

import "testing"

func BenchmarkPopCount(b *testing.B) {
	for i := 0; i < b.N; i++ {
		PopCount(uint64(i))
	}
}

func BenchmarkPopCount1000(b *testing.B) {
	for i := 0; i < b.N; i++ {
		for j := 0; j < 1000; j++ {
			PopCount(uint64(i))
		}
	}
}

func BenchmarkPopCountShift(b *testing.B) {
	for i := 0; i < b.N; i++ {
		PopCountShift(uint64(i))
	}
}

func BenchmarkPopCountShift1000(b *testing.B) {
	for i := 0; i < b.N; i++ {
		for j := 0; j < 1000; j++ {
			PopCountShift(uint64(i))
		}
	}
}

func BenchmarkPopCountRight(b *testing.B) {
	for i := 0; i < b.N; i++ {
		PopCountRight(uint64(i))
	}
}

func BenchmarkPopCountRight1000(b *testing.B) {
	for i := 0; i < b.N; i++ {
		for j := 0; j < 1000; j++ {
			PopCountRight(uint64(i))
		}
	}
}
