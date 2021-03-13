package pcshift

var pc [256]byte

func init() {
	for i := range pc {
		pc[i] = pc[i/2] + byte(i&1)
	}
}

func PopCount(x uint64) int {
	var r int
	for i := 0; i < 64; i++ {
		if (x>>i)&1 == 1 {
			r++
		}
	}
	return r
}
