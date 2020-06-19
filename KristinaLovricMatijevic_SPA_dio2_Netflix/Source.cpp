#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <map>
#include <queue>
#include <functional>
#include <list>
#include <string>
#include "MovieOrShow.h"
#include "Date.h"
#include "Utils.h"
#include <unordered_map>
#include "selection_sort.h"
#include "shell_sort.h"
#include "counting_sort.h"
#include <unordered_set>

using namespace std;
using namespace std::chrono;

template<typename T>
T get_rand(T min, T max)
{
	return rand() % (max - min + 1) + min;
}

void print(MovieOrShow& m)
{
	cout << m.to_string() << endl;
}

void parse_file(ifstream& in, vector<MovieOrShow>& v)
{
	string line;

	//eliminate header
	getline(in, line);

	//int i = 0;
	while (getline(in, line))
	{
		//cout << ++i << endl;

		string temp;
		vector<string> aux_parsed;

		//size_t = common type, string::size_type
		size_t end = 0, beg = 0;
		while (end != string::npos)
		{
			string column;

			end = line.find(',', beg);

			if (line.at(beg) == '"')
			{
				end = line.find("\",", beg);
				column = line.substr(beg + 1, end - beg - 1);
				aux_parsed.push_back(column);
				beg = end + 2;
			}
			else
			{
				column = line.substr(beg, end - beg);
				aux_parsed.push_back(column);
				beg = end + 1;
			}
		}

		MovieOrShow ms = MovieOrShow
		(
			aux_parsed.at(0),
			aux_parsed.at(1),
			aux_parsed.at(2),
			aux_parsed.at(3),
			aux_parsed.at(4),
			aux_parsed.at(5),
			aux_parsed.at(6),
			aux_parsed.at(7),
			aux_parsed.at(8),
			aux_parsed.at(9),
			aux_parsed.at(10),
			aux_parsed.at(11)
		);

		v.push_back(ms);
	}
}

void fill_map(vector<MovieOrShow>& main_data, map<string, MovieOrShow>& m)
{
	for (auto it = main_data.begin(); it != main_data.end(); ++it)
	{
		m.insert(pair<string, MovieOrShow>(it->get_show_id(), *it));
	}
}

void search_map_load_list(string& id, map<string, MovieOrShow>& m, list<MovieOrShow>& l)
{
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		if (it->first == id)
		{
			l.push_back(it->second);
		}
	}
}

void fill_multimap(vector<MovieOrShow>& main_data, multimap<int, MovieOrShow>& mm)
{
	for (auto it = main_data.begin(); it != main_data.end(); ++it)
	{
		mm.insert(pair<int, MovieOrShow>(it->get_release_year(), *it));
	}
}

void search_multimap_vector_list(int& year, multimap<int, MovieOrShow>& mm, vector<MovieOrShow>& main_data, list<MovieOrShow>& l)
{
	auto begin1 = high_resolution_clock::now();

	for (auto it = mm.begin(); it != mm.end(); ++it)
	{
		if (it->first == year)
		{
			cout << it->second.to_string() << endl;
		}
	}
	
	if (mm.count(year) == 0)
	{
		cout << "No movies/shows from this year!" << endl;
	}

	auto end1 = high_resolution_clock::now();
	auto dur_mmap = duration_cast<milliseconds>(end1 - begin1).count();


	auto begin2 = high_resolution_clock::now();

	for (auto it = main_data.begin(); it != main_data.end(); ++it)
	{
		if (it->get_release_year() == year)
		{
			cout << it->to_string() << endl;
		}
	}

	auto end2 = high_resolution_clock::now();
	auto dur_vector = duration_cast<milliseconds>(end2 - begin2).count();


	auto begin3 = high_resolution_clock::now();

	for (auto it = l.begin(); it != l.end(); ++it)
	{
		if (it->get_release_year() == year)
		{
			cout << it->to_string() << endl;
		}
	}

	auto end3 = high_resolution_clock::now();
	auto dur_list = duration_cast<milliseconds>(end3 - begin3).count();

	multimap<int, string> ranking;
	ranking.insert(pair<int, string>(dur_mmap, "- search in multimap"));
	ranking.insert(pair<int, string>(dur_vector, "- search in vector"));
	ranking.insert(pair<int, string>(dur_list, "- search in list"));

	for (auto it = ranking.begin(); it != ranking.end(); ++it)
	{
		cout << it->first << " ms " << it->second << endl;
	}
}

struct AscByYear
{
	bool operator() (MovieOrShow& ms1, MovieOrShow& ms2)
	{
		return ms1.get_release_year() > ms2.get_release_year();
	}
};

struct DescByYear
{
	bool operator() (MovieOrShow& ms1, MovieOrShow& ms2)
	{
		return ms1.get_release_year() < ms2.get_release_year();
	}
};

void show_content_desc(int& order, char& type, vector<MovieOrShow>& main_data)
{
	vector <MovieOrShow> movies;
	vector <MovieOrShow> shows;
	priority_queue <MovieOrShow, vector<MovieOrShow>, DescByYear> pq;

	for (auto it = main_data.begin(); it != main_data.end(); ++it)
	{
		if (it->get_type() == "Movie")
		{
			movies.push_back(*it);
		}
		else if (it->get_type() == "TV Show")
		{
			shows.push_back(*it);
		}
	}

	if (type == 'm')
	{
		priority_queue <MovieOrShow, vector<MovieOrShow>, DescByYear> pq(movies.begin(), movies.end());

		while (!pq.empty())
		{
			cout << pq.top().to_string() << endl;
			pq.pop();
		}
	}
	else if (type == 's')
	{
		priority_queue <MovieOrShow, vector<MovieOrShow>, DescByYear> pq(shows.begin(), shows.end());

		while (!pq.empty())
		{
			cout << pq.top().to_string() << endl;
			pq.pop();
		}
	}
}

void show_content_asc(int& order, char& type, vector<MovieOrShow>& main_data)
{
	vector <MovieOrShow> movies;
	vector <MovieOrShow> shows;
	priority_queue <MovieOrShow, vector<MovieOrShow>, AscByYear> pq;

	for (auto it = main_data.begin(); it != main_data.end(); ++it)
	{
		if (it->get_type() == "Movie")
		{
			movies.push_back(*it);
		}
		else if (it->get_type() == "TV Show")
		{
			shows.push_back(*it);
		}	
	}
	
	if (type == 'm')
	{
		priority_queue <MovieOrShow, vector<MovieOrShow>, AscByYear> pq(movies.begin(), movies.end());

		while (!pq.empty())
		{
			cout << pq.top().to_string() << endl;
			pq.pop();
		}
	}
	else if (type == 's')
	{
		priority_queue <MovieOrShow, vector<MovieOrShow>, AscByYear> pq(shows.begin(), shows.end());

		while (!pq.empty())
		{
			cout << pq.top().to_string() << endl;
			pq.pop();
		}
	}
}

//bool ismovie(MovieOrShow& ms)
//{
//	return ms.get_type() == "Movie";
//}
//
//void create_and_partition_pqs(vector<MovieOrShow>& main_data)
//{
//	partition(main_data.begin(), main_data.end(), ismovie);
//
//	priority_queue<MovieOrShow> pq(main_data.begin(), main_data.end());
//
//	for (auto it = main_data.begin(); it != main_data.end(); ++it)
//	{
//		cout << it->to_string() << endl;
//	}
//}

void selection_vs_shell_sort(vector<MovieOrShow>& main_data)
{
	//sortirati padajuæe -desc- po naslovu:
	//sortirati sa selection sortom
	vector<MovieOrShow> v1(main_data.begin(), main_data.end());
	int number_of_swaps_selection = 0;

	auto begin1 = high_resolution_clock::now();
	number_of_swaps_selection = selection_sort_by_title(v1, v1.size());
	auto end1 = high_resolution_clock::now();

	//for_each(v1.begin(), v1.end(), print);
	cout << "Selection sort duration: " << duration_cast<milliseconds>(end1 - begin1).count() << " ms" << endl;
	cout << "Selection sort swaps: " << number_of_swaps_selection << endl;

	//sortirati sa shell sortom
	vector<MovieOrShow> v2(main_data.begin(), main_data.end());
	int number_of_swaps_shell = 0;

	auto begin2 = high_resolution_clock::now();
	number_of_swaps_shell = number_of_swaps_shell = shell_sort_by_title(v2, v2.size());
	auto end2 = high_resolution_clock::now();

	//for_each(v2.begin(), v2.end(), print);
	cout << "Shell sort duration: " << duration_cast<milliseconds>(end2 - begin2).count() << " ms" << endl;
	cout << "Shell sort swaps: " << number_of_swaps_shell << endl;

	//ispisati koliko je trajalo svako sortiranje
} 

void lets_play_guess() {
	long random_max_value = get_rand(1, 100000000);
	long time_estimate = 0;
	bool is_element_found = false;

	cout << "Enter time estimation to shuffle, sort and binary search the vector of " << random_max_value << " elements in us: " << endl;
	cin >> time_estimate;

	auto begin = high_resolution_clock::now();
	// create and populate vector
	vector<long> values;
	for (long i = 1; i < random_max_value; i++) {
		values.push_back(i);
	}
	// shuffle vector
	random_shuffle(values.begin(), values.end());
	// binary sort vector
	sort(values.begin(), values.end());
	// binary search number 13
	is_element_found = binary_search(values.begin(), values.end(), 13);
	auto end = high_resolution_clock::now();

	long actual_time_diff = duration_cast<microseconds>(end - begin).count();

	if (is_element_found) {
		cout << "User duration estimate: " << time_estimate << endl;
		cout << "Actual duration: " << actual_time_diff << endl;
		cout << "Difference estimate/actual: " << time_estimate - actual_time_diff << endl;
	}
	else {
		cout << "Element not found" << endl;
	}
}

void counting_sort() {
	// enter max value
	int max_value = 0;
	cout << "Enter max element value: " << endl;
	cin >> max_value;

	// create vector with 100.000 random elements between 1 and max_value
	vector<int> values;
	for (int i = 0; i < 100000; i++) {
		values.push_back(get_rand(1, max_value));
	}

	// sort vector using Counting sort
	counting_sort(values, values.size());
}

void fill_unordered_multimap(vector<MovieOrShow>& main_data, unordered_multimap<string, MovieOrShow>& ummap)
{
	for (auto it = main_data.begin(); it != main_data.end(); ++it)
	{
		ummap.insert(pair<string, MovieOrShow> (it->get_title(), *it));
	}
}

void search_unordered_multimap_vector2_list2(string& title, unordered_multimap<string, MovieOrShow>& ummap, vector<MovieOrShow>& main_data, list<MovieOrShow> l)
{
	auto begin1 = high_resolution_clock::now();

	for (auto it = ummap.begin(); it != ummap.end(); ++it)
	{
		if (it->first == title)
		{
			cout << it->second.to_string() << endl;
		}
	}

	if (ummap.count(title) == 0)
	{
		cout << "No movies/shows with this title!" << endl;
	}

	auto end1 = high_resolution_clock::now();
	auto dur_ummap = duration_cast<milliseconds>(end1 - begin1).count();


	auto begin2 = high_resolution_clock::now();

	for (auto it = main_data.begin(); it != main_data.end(); ++it)
	{
		if (it->get_title() == title)
		{
			cout << it->to_string() << endl;
		}
	}

	auto end2 = high_resolution_clock::now();
	auto dur_vector2 = duration_cast<milliseconds>(end2 - begin2).count();

	auto begin3 = high_resolution_clock::now();

	for (auto it = l.begin(); it != l.end(); ++it)
	{
		if (it->get_title() == title)
		{
			cout << it->to_string() << endl;
		}
	}

	auto end3 = high_resolution_clock::now();
	auto dur_list2 = duration_cast<milliseconds>(end3 - begin3).count();

	multimap<int, string> ranking;
	ranking.insert(pair<int, string>(dur_ummap, "- search in multimap"));
	ranking.insert(pair<int, string>(dur_vector2, "- search in vector"));
	ranking.insert(pair<int, string>(dur_list2, "- search in list"));

	for (auto it = ranking.begin(); it != ranking.end(); ++it)
	{
		cout << it->first << " ms " << it->second << endl;
	}
}

void fill_unordered_map(vector<MovieOrShow>& main_data, unordered_map<string, MovieOrShow>& umap)
{
	for (auto it = main_data.begin(); it != main_data.end(); ++it)
	{
		umap.insert(pair<string, MovieOrShow>(it->get_show_id(), *it));
	}
}

void load_multiset(string& title1, unordered_multiset<char>& anagram)
{
	for (int i = 0; i < title1.length(); i++)
	{
		anagram.insert(title1[i]);
	}
}

void search_multiset(string& title2, unordered_multiset<char>& anagram)
{
	for (int i = 0; i < title2.length(); i++)
	{
		for (auto it = anagram.begin(); it != anagram.end(); ++it)
		{
			if (*it != title2[i])
			{
				cout << "Not an anagram!" << endl;
			}
			else
			{
				cout << "Anagram!" << endl;
			}
		}
	}
}

void bogosort(vector<MovieOrShow>& v)
{
	int tries = 0;
	
	for (auto it1 = v.begin(); it1 != v.end(); ++it1)
	{
		for (auto it2 = v.begin(); it2 != v.end(); ++it2)
		{
			while (it1->get_title() < it2->get_title())
			{
				random_shuffle(v.begin(), v.end());
				tries++;
			}	
		}
	}
	
	cout << "Number of tries: " << tries << endl << endl;
	for_each(v.begin(), v.end(), print);
}

void load_vector_for_bogo(vector<MovieOrShow>& main_data, vector<MovieOrShow>& v)
{
	for (int i = 0; i < 3; i++)
	{
		int random_index = get_rand<int>(0, main_data.size());
		v.push_back(main_data.at(random_index));
	}
}

char menu()
{
	//system("cls");

	cout << endl;
	cout << "Welcome to SPA_Netflix console application." << endl;
	cout << "What do you want to do?" << endl << endl;
	cout << "a - Search by release year" << endl;
	cout << "b - View by release year" << endl;
	cout << "c - Copy to new list" << endl;
	cout << "d - View by type" << endl;
	cout << "e - Selection vs Shell" << endl;
	cout << "f - Let's play guess" << endl;
	cout << "g - Monkey Play" << endl;
	cout << "h - Counting" << endl;
	cout << "i - Search by title" << endl;
	cout << "j - Visualize" << endl;
	cout << "k - Making anagrams" << endl;
	cout << "Enter option: ";

	char c;
	cin >> c;
	cin.ignore();
	return c;
}

int main()
{
	srand(time(nullptr));

	char main_menu_choice;

	ifstream in("SPA_PROJ_004_NETFLIX_data.csv");
	
	if (!in)
	{
		cout << "Unable to open file" << endl;
		return 1;
	}

	vector<string> aux_parsed;
	vector<MovieOrShow> main_data;
	multimap<int, MovieOrShow> mm;
	list<MovieOrShow> l;
	map<string, MovieOrShow> m;
	bool more;
	string id;
	unordered_multimap<string, MovieOrShow> ummap;
	string title;
	unordered_map<string, MovieOrShow> umap;
	vector<MovieOrShow> v;
	string title1;
	string title2;
	unordered_multiset<char> anagram;

	do
	{
		main_menu_choice = menu();
		switch (main_menu_choice)
		{

		case 'a':
			parse_file(in, main_data);
			//printing main_data:
			//for_each(main_data.begin(), main_data.end(), print);
			in.close();
			fill_multimap(main_data, mm);

			int year;
			cout << "Enter release year: " << endl;
			cin >> year;

			for (auto it = main_data.begin(); it != main_data.end(); ++it)
			{
				l.push_back(*it);
			}

			search_multimap_vector_list(year, mm, main_data, l);
			break;

		case 'b':
			parse_file(in, main_data);
			in.close();

			char type;
			cout << "Do you want to display movies or shows?" << endl << "Type m for movies, s for shows: " << endl;
			cin >> type;

			int order;
			cout << "Do you want to display asc or desc?" << endl << "Type 0 for asc, 1 for desc: " << endl;
			cin >> order;
			cin.ignore();

			if (order == 0)
			{
				show_content_asc(order, type, main_data);
			}
			else if (order == 1)
			{
				show_content_desc(order, type, main_data);
			}
			break;

		case 'c':
			parse_file(in, main_data);
			in.close();
			
			fill_map(main_data, m);

			do
			{
				cout << "Enter Show ID: " << endl;
				cin >> id;
				
				search_map_load_list(id, m, l);

				cout << "Want to enter one more ID? Press 1 for Yes, 0 for No" << endl;
				cin >> more;
				cin.ignore();

			} while (more);

			for_each(l.begin(), l.end(), print);

			break;

		case 'd':
			parse_file(in, main_data);
			in.close();
		
			break;

		case 'e':
			parse_file(in, main_data);
			in.close();

			selection_vs_shell_sort(main_data);
			
			break;

		case 'f':
			lets_play_guess();
			break;

		case 'h':
			counting_sort();
			break;

		case 'g':
			parse_file(in, main_data);
			in.close();

			load_vector_for_bogo(main_data, v);
			bogosort(v);
			v.clear();

			break;

		case 'i':
			parse_file(in, main_data);
			in.close();

			fill_unordered_multimap(main_data, ummap);

			cout << "Enter the title you want to search: " << endl;
			getline (cin, title);
					
			for (auto it = main_data.begin(); it != main_data.end(); ++it)
			{
				l.push_back(*it);
			}

			search_unordered_multimap_vector2_list2(title, ummap, main_data, l);
			break;

		case 'j':
			parse_file(in, main_data);
			in.close();

			fill_unordered_map(main_data, umap);

			for (int i = 0; i < umap.bucket_count(); i++)
			{
				cout << "Bucket " << i << ": ";

				for (auto it = umap.begin(i); it != umap.end(i); ++it)
				{

					if (next(it) == umap.end(i))
					{
						cout << it->second.get_title();
					}
					else if (umap.bucket_size(i) == 0.0)
					{
						cout << "[EMPTY]";
					}
					else
					{
						cout << it->second.get_title() << " -- ";
					}
				}
				cout << endl;
			}
			break;

		case 'k':
			/*parse_file(in, main_data);
			in.close();*/

			cout << "Enter the first title: ";
			getline(cin, title1);
			
			cout << "Enter the second title: ";
			getline(cin, title2);
			
			load_multiset(title1, anagram);
			search_multiset(title2, anagram);

			break;

		default:
			cout << "Press any key to continue or x to exit" << endl;
			cin.ignore();
		}

	} while (main_menu_choice != 'x');


	return 0;
}