#include <iostream>
#include "Date.h"

size_t StringToInt(std::string str)
{
	size_t nr = 0;
	for (size_t i = 0; i < str.size(); i++) {
		nr *= 10;
		nr += str[i] - '0';
	}
	return nr;
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
		puts("Usage:"
			"\nReq: DATE"
			"\nReq: MONTHS TO PASS"
			"\nOpt: FORMAT    (def = -mf):"
			"\n\t-df    DD/MM/YYYY"
			"\n\t-mf    MM/DD/YYYY\n");
		return -1;
	}

	if (argc == 4) {
		char* ChSformat = argv[3];
		if (!(ChSformat[1] == 'd' || ChSformat[1] == 'm')) {
			puts("Invalid format!\n");
			return -2;
		}
		if (ChSformat[1] == 'd')
			English_Date_Format = 0;
	}

	char* ChSdate = argv[1];

	if (!IsValidDate(ChSdate)) {
		puts("Invalid date!\n");
		return -3;
	}

	Date date = CreateDate(ChSdate);

	size_t monthsToPass = StringToInt(argv[2]);

	size_t daysPassed = 0;

	if (date.month == 2)
		daysPassed += IsLeapYear(date.year) ? 29 : 28;
	else
		daysPassed += (date.month % 2) ? 31 : 30;
	daysPassed -= date.day;

	for (size_t i = 1; i <= monthsToPass; i++)
		if((date.month + i) % 12 == 2)
			daysPassed += IsLeapYear(date.year + i % 12) ? 29 : 28;
		else
			daysPassed += (date.month + i) % 12 % 2 ? 31 : 30;

	printf("%d", daysPassed);
}