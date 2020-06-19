#pragma once
#include <string>

using namespace std;

class Date
{

public:
	Date();
	Date(string date);
	Date(int day, int month, int year);
	void set_month(int month);
	void set_day(int day);
	void set_year(int year);
	int get_month();
	int get_day();
	int get_year();
	string to_string();

private:
	int month;
	int day;
	int year;
	int convert_month(string month);
	void parse_date(string date_added);
};
