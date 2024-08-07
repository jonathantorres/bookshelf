#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                             {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int main(void)
{
    int y = 1984, m = 6, d = 30, yd = 325;
    int pm, pd;

    printf("Day: %d\n", day_of_year(y, m, d));
    month_day(y, yd, &pm, &pd);
    printf("Month: %d, Day: %d\n", pm, pd);

    return 0;
}

int day_of_year(int year, int month, int day)
{
    int i, leap;
    char *p;
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    p    = daytab[leap];

    if (month < 1 || month > 12) {
        return -1;
    }

    if (day < 1 || day > *(p + month)) {
        return -1;
    }

    for (i = 1; i < month; i++) {
        day += *p++;
    }

    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    char *p;
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    p    = daytab[leap];

    if (leap) {
        if (yearday > 365) {
            *pmonth = -1;
            *pday   = -1;
            return;
        }
    } else {
        if (yearday > 366) {
            *pmonth = -1;
            *pday   = -1;
            return;
        }
    }

    for (i = 1; yearday > *p; i++, p++) {
        yearday -= *p;
    }

    *pmonth = i;
    *pday   = yearday;
}
