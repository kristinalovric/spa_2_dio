#include "MovieOrShow.h"
#include <sstream>
#include <string>
#include <iostream>
#include "Utils.h"

using namespace std;


MovieOrShow::MovieOrShow()
{
}

MovieOrShow::MovieOrShow(string show_id, string type, string title, string director, string cast, string country, string date_added, string release_year, string rating, string duration, string genre, string description)
{
	set_show_id(show_id);
	set_type(type);
	set_title(title);
	set_director(director);
	set_cast(cast);
	set_country(country);
	set_date_added(date_added);
	set_release_year(release_year);
	set_rating(rating);
	set_duration(duration);
	set_genre(genre);
	set_description(description);

}

void MovieOrShow::set_show_id(string show_id)
{
	this->show_id = show_id;
}

void MovieOrShow::set_type(string type)
{
	this->type = type;
}

void MovieOrShow::set_title(string title)
{
	this->title = title;
}

void MovieOrShow::set_director(string director)
{
	parse_fields(director, directors);
}

void MovieOrShow::set_cast(string cast)
{
	parse_fields(cast, actors);
}

void MovieOrShow::set_country(string country)
{
	parse_fields(country, countries);
}

void MovieOrShow::set_date_added(string date_added)
{
	this->date_added = Date(date_added);
}

void MovieOrShow::set_release_year(string release_year)
{
	if (!release_year.empty())
	{
		this->release_year = stoi(Utils::trim(release_year));
	}
}

void MovieOrShow::set_rating(string rating)
{
	this->rating = rating;
}

void MovieOrShow::set_duration(string duration)
{
	this->duration = duration;
}

void MovieOrShow::set_genre(string genre)
{
	parse_fields(genre, genres);
}

void MovieOrShow::set_description(string description)
{
	this->description = description;
}

vector<string> MovieOrShow::get_actors()
{
	return actors;
}

vector<string> MovieOrShow::get_directors()
{
	return directors;
}

string MovieOrShow::get_show_id() const
{
	return show_id;
}

string MovieOrShow::get_type() const
{
	return type;
}

vector<string> MovieOrShow::get_countries()
{
	return countries;
}

string MovieOrShow::get_title() const
{
	return title;
}

int MovieOrShow::get_release_year() const
{
	return release_year;
}

vector<string> MovieOrShow::get_genres()
{
	return genres;
}

Date MovieOrShow::get_date_added() const
{
	return date_added;
}

string MovieOrShow::get_description() const
{
	return description;
}

string MovieOrShow::to_string() const
{
	stringstream ss;
	ss << "ShowId: " << get_show_id() << " Title: " << get_title() << ", year of production: " << get_release_year() << ", type: " << get_type() << ", description: " << get_description() << ", " << get_date_added().to_string() << endl;
	return ss.str();
}

int MovieOrShow::get_release_decade()
{
	return this->release_year - (this->release_year % 10);
}

void MovieOrShow::parse_fields(string input, vector<string>& v)
{
	if (input.empty())
	{
		return;
	}

	stringstream ss(input);
	string temp;

	while (getline(ss, temp, ','))
	{
		v.push_back(temp);
	}
}

string MovieOrShow::print_fields(vector<string>& v) const
{
	stringstream ss;
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		ss << *it << " ";
	}

	return ss.str();
}