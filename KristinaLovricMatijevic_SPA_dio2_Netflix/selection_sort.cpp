#include "selection_sort.h"

using namespace std;

void selection_sort(int data[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < n; j++) {
			if (data[j] < data[min_index]) {
				min_index = j;
			}
		}

		swap(data[min_index], data[i]);
	}
}

int selection_sort_by_title(vector<MovieOrShow>& data, const int& n) {
	int number_of_swaps = 0;

	for (int i = 0; i < n - 1; i++) {
		int min_index = i;

		for (int j = i + 1; j < n; j++) {
			if (data.at(j).get_title() > data.at(min_index).get_title()) {
				min_index = j;
			}
		}

		if (min_index != i) {
			swap(data.at(min_index), data.at(i));
			number_of_swaps++;
		}
	}

	return number_of_swaps;
}