#include "Date.h"
#include "Utils.h"
#include <sstream>

using namespace std;

Date::Date()
{
	set_day(0);
	set_month(0);
	set_year(0);
}

Date::Date(string date)
{
	if (date.empty())
	{
		set_month(0);
		set_day(0);
		set_year(0);
	}
	else
	{
		parse_date(date);
	}
}

Date::Date(int month, int day, int year)
{
	set_month(month);
	set_day(day);
	set_year(year);
}

void Date::set_month(int month)
{
	this->month = month;
}

void Date::set_day(int day)
{
	this->day = day;
}

void Date::set_year(int year)
{
	this->year = year;
}

int Date::get_month()
{
	return month;
}

int Date::get_day()
{
	return day;
}

int Date::get_year()
{
	return year;
}

string Date::to_string()
{
	stringstream ss;
	ss << "Date added (day-month-year): " << get_day() << "-" << get_month() << "-" << get_year();
	return ss.str();
}

int Date::convert_month(string month)
{
	if (month == "January")
	{
		return 1;
	}
	else if (month == "February")
	{
		return 2;
	}
	else if (month == "March")
	{
		return 3;
	}
	else if (month == "April")
	{
		return 4;
	}
	else if (month == "May")
	{
		return 5;
	}
	else if (month == "June")
	{
		return 6;
	}
	else if (month == "July")
	{
		return 7;
	}
	else if (month == "August")
	{
		return 8;
	}
	else if (month == "September")
	{
		return 9;
	}
	else if (month == "October")
	{
		return 10;
	}
	else if (month == "November")
	{
		return 11;
	}
	else if (month == "December")
	{
		return 12;
	}
}

template<typename T> T convert(string& s)
{
	stringstream c(s);
	T t;
	c >> t;
	return t;
}

void Date::parse_date(string date_added)
{
	Utils::trim(date_added);
	stringstream ss(date_added);
	string temp;

	getline(ss, temp, ' ');
	set_month(convert_month(temp));

	getline(ss, temp, ',');
	set_day(convert<int>(temp));

	getline(ss, temp);
	set_year(convert<int>(Utils::trim(temp)));
}

