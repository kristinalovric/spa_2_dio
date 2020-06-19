#include "Utils.h"

string& Utils::ltrim(string& str, const string& chars)
{
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

string& Utils::rtrim(string& str, const string& chars)
{
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

string& Utils::trim(string& str, const string& chars)
{
	return ltrim(rtrim(str, chars), chars);
}
