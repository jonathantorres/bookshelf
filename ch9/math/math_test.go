package math

import "testing"

type testpair struct {
	values []float64
	result float64
}

var avgTests = []testpair{
	{
		values: []float64{},
		result: 0,
	},
	{
		values: []float64{1, 2},
		result: 1.5,
	},
}

var minTests = []testpair{
	{
		values: []float64{},
		result: 0,
	},
	{
		values: []float64{1, 2},
		result: 1,
	},
	{
		values: []float64{11, 55, 30, 30, 60, 98},
		result: 11,
	},
}

var maxTests = []testpair{
	{
		values: []float64{},
		result: 0,
	},
	{
		values: []float64{1, 2},
		result: 2,
	},
	{
		values: []float64{11, 55, 30, 30, 60, 98},
		result: 98,
	},
}

func TestAverage(t *testing.T) {
	for _, pair := range avgTests {
		avg := Average(pair.values)
		if avg != pair.result {
			t.Error("For", pair.values, "expected", pair.result, "got", avg)
		}
	}
}

func TestMin(t *testing.T) {
	for _, pair := range minTests {
		min := Min(pair.values)
		if min != pair.result {
			t.Error("For", pair.values, "expected", pair.result, "got", min)
		}
	}
}

func TestMax(t *testing.T) {
	for _, pair := range maxTests {
		max := Max(pair.values)
		if max != pair.result {
			t.Error("For", pair.values, "expected", pair.result, "got", max)
		}
	}
}
