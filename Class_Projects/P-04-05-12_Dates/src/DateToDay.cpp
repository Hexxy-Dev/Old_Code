#include <iostream>
#include "Date.h"

constexpr char* days[] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

const char* GetDayOfWeek(Date date)
{
	int day = date.day;

	uint8_t month = date.month;
	month += month < 3 ? 10 : -2;

	uint16_t year = date.year % 100 - (month > 10);

	uint8_t century = date.year / 100;

	uint8_t dayOfWeek = (day + (int)floor(2.6 * month - 0.2) - 2 * century
		+ year + year / 4 + century / 4) % 7;

	return days[dayOfWeek];
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
		puts("Usage:"
			"\nReq: DATE"
			"\nOpt: FORMAT    (def = -mf):"
			"\n\t-df    DD/MM/YYYY"
			"\n\t-mf    MM/DD/YYYY\n");
		return -1;
	}

	if (argc == 3) {
		char* ChSformat = argv[2];
		if (!(ChSformat[1] == 'd' || ChSformat[1] == 'm')) {
			puts("Invalid format!\n");
			return -2;
		}
		if(ChSformat[1] == 'd')
			English_Date_Format = 0;
	}

	char* ChSdate = argv[1];

	if (!IsValidDate(ChSdate)) {
		puts("Invalid date!\n");
		return -3;
	}

	Date date = CreateDate(ChSdate);

	printf("%s", GetDayOfWeek(date));
}