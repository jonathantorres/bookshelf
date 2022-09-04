package main

import "fmt"

func main() {
	var y, m, d, yd int = 1984, 6, 30, 325
	var pm, pd int
	fmt.Printf("Day: %d\n", day_of_year(y, m, d))
	month_day(y, yd, &pm, &pd)
	fmt.Printf("Month: %d, Day: %d\n", pm, pd)
}

var daytab [2][13]int = [2][13]int{
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
}

func day_of_year(year int, month int, day int) int {
	var i, leap int
	if (year%4 == 0 && year%100 != 0) || year%400 == 0 {
		leap = 1
	} else {
		leap = 0
	}
	if month < 1 || month > 12 {
		fmt.Printf("error: invalid month!\n")
		return -1
	}
	if day < 1 || day > daytab[leap][month] {
		fmt.Printf("error: invalid day!\n")
		return -1
	}
	for i = 1; i < month; i++ {
		day += daytab[leap][i]
	}
	return day
}

func month_day(year int, yearday int, pmonth *int, pday *int) {
	var i, leap int
	if (year%4 == 0 && year%100 != 0) || year%400 == 0 {
		leap = 1
	} else {
		leap = 0
	}
	if leap > 0 {
		if yearday > 365 {
			fmt.Printf("error: not a valid day!\n")
			return
		}
	} else {
		if yearday > 366 {
			fmt.Printf("error: not a valid day!\n")
			return
		}
	}
	for i = 1; yearday > daytab[leap][i]; i++ {
		yearday -= daytab[leap][i]
	}
	*pmonth = i
	*pday = yearday
}
