#include "shell_sort.h"
#include <algorithm>
using namespace std;

void shell_sort(int data[], int n) {
	for (int step = n / 2; step > 0; step = step / 2) {
		for (int i = step; i < n; i++) { // Izrada potpolja
			for (int j = i - step; j >= 0; j -= step) { // Insertion na potpolju
				if (data[j] > data[j + step]) {
					swap(data[j], data[j + step]);
				}
			}
		}
	}
} 

int shell_sort_by_title(vector<MovieOrShow>& data, const int& n) {
	int number_of_swaps = 0;

	for (int step = n / 2; step > 0; step = step / 2) {
		for (int i = step; i < n; i++) { // Izrada potpolja
			for (int j = i - step; j >= 0; j -= step) { // Insertion na potpolju
				if (data.at(j).get_title() < data.at(static_cast<int64_t>(j) + step).get_title()) {
					swap(data.at(j), data.at(static_cast<int64_t>(j) + step));
					number_of_swaps++;
				}
			}
		}
	}

	return number_of_swaps;
}