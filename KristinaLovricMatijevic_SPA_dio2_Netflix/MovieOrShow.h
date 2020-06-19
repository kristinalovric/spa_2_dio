#pragma once
#include <string>
#include <vector>
#include "Date.h"

using namespace std;

class MovieOrShow
{

public:
	MovieOrShow();
	MovieOrShow(string show_id, string type, string title, string director, string cast, string country, string date_added, string release_year, string rating, string duration, string genre, string description);

	void set_show_id(string show_id);
	void set_type(string type);
	void set_title(string title);
	void set_director(string director);
	void set_cast(string cast);
	void set_country(string country);
	void set_date_added(string date_added);
	void set_release_year(string release_year);
	void set_rating(string rating);
	void set_duration(string duration);
	void set_genre(string genre);
	void set_description(string description);

	vector<string> get_actors();
	vector<string> get_directors();
	vector<string> get_countries();
	vector<string> get_genres();
	Date get_date_added() const;
	string get_title() const;
	int get_release_year() const;
	string get_show_id() const;
	string get_type() const;
	string get_description() const;
	string to_string() const;
	int get_release_decade();


private:
	string show_id;
	string type;
	string title;
	Date date_added;
	int release_year;
	string rating;
	string duration;
	vector<string> genres;
	string description;
	vector<string> directors;
	vector<string> actors;
	vector<string> countries;

	void parse_fields(string input, vector<string>& v);

	string print_fields(vector<string>& v) const;



};

