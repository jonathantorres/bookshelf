package popcount

// Exercise 11.6

// pc[i] is the population count of i
var pc [256]byte

func init() {
	for i := range pc {
		pc[i] = pc[i/2] + byte(i&1)
	}
}

// PopCount returns the population count (number of set bits) of x
func PopCount(x uint64) int {
	var count int
	for i := 0; i < 8; i++ {
		count += int(pc[byte(x>>uint(i*8))])
	}
	return count
}

func PopCountShift(x uint64) int {
	count := 0
	mask := uint64(1)
	for i := 0; i < 64; i++ {
		if x&mask > 0 {
			count++
		}
		x >>= 1
	}
	return count
}

func PopCountRight(x uint64) int {
	count := 0
	for x != 0 {
		x &= x - 1
		count++
	}
	return count
}
