package main

import "fmt"

func main() {
	nums := []int{12, 14, 77, 99, 101, 189, 293, 890, 991, 1065}
	fmt.Printf("%d\n", binsearch(77, nums))  // 2
	fmt.Printf("%d\n", binsearch2(66, nums)) // -1
}

func binsearch2(x int, v []int) int {
	var low, high, mid int
	n := len(v)
	high = n - 1
	for {
		if low > high || v[mid] == x {
			break
		}
		mid = (low + high) / 2
		if x < v[mid] {
			high = mid - 1
		} else {
			low = mid + 1
		}
	}
	if v[mid] == x {
		return mid
	}
	return -1
}

func binsearch(x int, v []int) int {
	var low, high, mid int
	n := len(v)
	high = n - 1
	for {
		if low > high {
			break
		}
		mid = (low + high) / 2
		if x < v[mid] {
			high = mid - 1
		} else if x > v[mid] {
			low = mid + 1
		} else {
			return mid
		}
	}
	return -1
}
