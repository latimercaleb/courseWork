
#include "Date.h"
#include <ctime>

Date::Date()
{
	time_t t = time(NULL);   
	struct tm *today = localtime(&t);
	year = today->tm_year + 1900;
	month = today->tm_mon +1;
	day = today->tm_mday;
}

Date::Date(int d, int m, int y) throw (logic_error)
{
	if ((m < 1) || (m>12))
		throw;
		else if ((d < 0) || (d > daysInMonth(m, y)))
			throw;
		else
		{
			day = d;
			month = m;
			year = y;
		}
}

int Date::getDay() const
{
	return day; 
}

int Date::getMonth() const
{
	return month;  
}

int Date::getYear() const
{
	return year; 
}

//in show2.cpp
//void showStructure() const;


bool Date::isLeapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
	
}

int Date::daysInMonth(int month, int year)
{
	switch (month)
	{
	case 1:
		return 31;
	case 2:
		if (isLeapYear)
		{
			return 29;
		}
		else
			return 28;
	case 3:
		return 31;
	case 4:
		return 30;
		break;
	case 5:
		return 31;
		break;
	case 6:
		return 30;
		break;
	case 7:
		return 31;
		break;
	case 8:
		return 31;
		break;
	case 9:
		return 30;
		break;
	case 10:
		return 31;
		break;
	case 11:
		return 30;
		break;
	case 12:
		return 31;
		break; 
	}
}

int Date::getDayOfWeek() const
{
	tm timeStruct = {};
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;
	timeStruct.tm_hour = 12;
	mktime(&timeStruct);
	return timeStruct.tm_wday;
	/*int monthnum, daynum, yrnum;
	switch (month)
	{
	case 1: monthnum = 6;
		break;
	case 2: monthnum = 2;
		break;
	case 3: monthnum = 2;
		break;
	case 4: monthnum = 5;
		break;
	case 5: monthnum = 0;
		break;
	case 6: monthnum = 3;
		break;
	case 7: monthnum = 5;
		break;
	case 8: monthnum = 1;
		break;
	case 9: monthnum = 4;
		break;
	case 10: monthnum = 6;
		break;
	case 11: monthnum = 2;
		break;
	case 12: monthnum = 4;
		break;

	}
	switch (day)
	{
	case 1: daynum = 6;
		break;
	case 2: daynum = 2;
		break;
	case 3: monthnum = 2;
		break;
	case 4: monthnum = 5;
		break;
	case 5: monthnum = 0;
		break;
	case 6: monthnum = 3;
		break;
	case 7: monthnum = 5;
		break;
	}*/
	/*time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	return timePtr->tm_wday;*/
}

bool Date::operator<(const Date& rhs) const
{
	if (year < rhs.year)
		return true;
	else if (year == rhs.year)
	{
		if (month < rhs.month)
			return true;
		else if (month == rhs.month)
		{
			if (day < rhs.day)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false; 
	
}

bool Date::operator==(const Date& rhs) const
{
	if ((month == rhs.month) && (day == rhs.day) && (year == rhs.year))
		return true;
	else
		return false;
}

bool Date::operator>(const Date& rhs) const
{
		if (year > rhs.year)
			return true;
		else if (year == rhs.year)
		{
			if (month > rhs.month)
				return true;
			else if (month == rhs.month)
			{
				if (day > rhs.day)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;

}

ostream& operator<<(ostream& out, const Date& date)
{
	out<< date.month << '/' << date.day <<'/' << date.year;
	return out;
}