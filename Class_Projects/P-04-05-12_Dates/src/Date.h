#pragma once
#include <stdint.h>
#include <string>

#define GENERAL_DATE_LENGTH 10

bool English_Date_Format = 1;	//0 DD/MM/YYYY
								//1 MM/DD/YYYY

bool IsLeapYear(uint16_t year) { return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)); }

struct Date {
	uint8_t day;
	uint8_t month;
	uint16_t year;
};

Date CreateDate(std::string Sdate)
{
	for (uint8_t i = 0; i < GENERAL_DATE_LENGTH; i++)
		Sdate[i] -= '0';
	Date date;

	date.day = Sdate[0] * 10 + Sdate[1];
	date.month = Sdate[3] * 10 + Sdate[4];

	if (English_Date_Format) {
		uint8_t tmp = date.day;
		date.day = date.month;
		date.month = tmp;
	}

	date.year = Sdate[6] * 1000 + Sdate[7] * 100 + Sdate[8] * 10 + Sdate[9];

	return date;
}

bool IsValidDate(std::string Sdate)
{
	if (Sdate.size() != GENERAL_DATE_LENGTH)
		return false;

	for (uint8_t i = 0; i < GENERAL_DATE_LENGTH; i++)
		if ((Sdate[i] < '0' || Sdate[i] > '9') && Sdate[i] != '/')
			return false;

	Date date = CreateDate(Sdate);

	if (date.day > 31 || date.month > 12)
		return false;
	if(date.month == 2)
		if (IsLeapYear(date.year)) {
			if (date.day > 29)
				return false;
		} else
			if (date.day > 28)
				return false;
		
	return true;
}