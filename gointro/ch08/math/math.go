package math

// Gets the average of a slice of floats
func Average(nums []float64) float64 {
	var total float64
	for _, num := range nums {
		total += num
	}
	return total / float64(len(nums))
}

func Min(nums []float64) float64 {
	var min float64
	for i, num := range nums {
		if i == 0 || num < min {
			min = num
		}
	}
	return min
}

func Max(nums []float64) float64 {
	var max float64
	for i, num := range nums {
		if i == 0 || num > max {
			max = num
		}
	}
	return max
}
