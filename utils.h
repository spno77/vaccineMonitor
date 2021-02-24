#ifndef UTILS_H_
#define UTILS_H_

typedef struct Date{
	int day;
	int month;
	int year;
}Date;


Date *stringToDate(char *dateStr);

void printDate(Date *date);

void compareDates(Date *d1,Date *d2);

#endif