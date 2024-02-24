#include <iostream>
#include "Date.h"

//https://ytliu0.github.io/ChineseCalendar/rules.html#rules

//http://en.chinaculture.org/focus/focus/2010dongzhi/2010-12/22/content_402244.htm
inline Date WinterSolstice(Date date)
{ return {uint8_t(0.0f + date.year % 100 * 0.2422 + (date.year / 100 == 19 ? 22.60 : 21.94)
	- date.year % 100 / 4 - (date.year == 1918 || date.year == 2021? 1 : 0)), 12, date.year }; }


Date LunarConjunction(Date date, int8_t dir)
{

}

int main(int argc, char* argv[])
{
	//if (argc == 1) {
	//	puts("Usage:"
	//		"\nReq: DATE"
	//		"\nOpt: FORMAT    (def = -mf):"
	//		"\n\t-df    DD/MM/YYYY"
	//		"\n\t-mf    MM/DD/YYYY\n");
	//	return -1;
	//}
	//
	//if (argc == 3) {
	//	char* ChSformat = argv[2];
	//	if (!(ChSformat[1] == 'd' || ChSformat[1] == 'm')) {
	//		puts("Invalid format!\n");
	//		return -2;
	//	}
	//	if (ChSformat[1] == 'd')
	//		English_Date_Format = 0;
	//}
	//
	//char* ChSdate = argv[1];
	//
	//if (!IsValidDate(ChSdate)) {
	//	puts("Invalid date!\n");
	//	return -3;
	//}
	//
	//Date date = CreateDate(ChSdate);

	Date date = { 28,2,2017 };

	Date WY = WinterSolstice(date);
	Date WY1 = WinterSolstice({ date.day, date.month, uint16_t(date.year - 1) });

	Date M1 = LunarConjunction(WY1, -1);
	Date M11 = LunarConjunction(WY, 1);

	uint8_t LY = round(double(M11.day - M1.day) / 29.53);


	//if(LY == 12)

	//if(LY == 13)
}