#ifndef UTILS_H_
#define UTILS_H_

typedef struct Date{
	int day;
	int month;
	int year;
}Date;


Date *stringToDate(char *dateStr);

void printDate(Date *date);

//TODO
void compareDates(Date *d1,Date *d2);

void readFile(char *filename);

#endif