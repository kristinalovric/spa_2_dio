#include <iostream>
#include "counting_sort.h"


int max_element(vector<int>& data, const int& n) {
	int max = data.at(0);
	for (int i = 1; i < n; i++) {
		if (data.at(i) > max) {
			max = data.at(i);
		}
	}
	return max;
}

vector<int> napravi_polje(int n) {
	vector<int>polje;
	for (int i = 0; i < n; i++) {
		polje.push_back(0);
	}
	return polje;
}

void ispisi_sljedeci_indeks(const vector<int>& sljedeci_indeks) {
	for (int i = 0; i < sljedeci_indeks.size(); i++) {
		cout << sljedeci_indeks.at(i) << " ";
		if (i == sljedeci_indeks.size() - 1)
			cout << endl;
	}
}

void prebroji_ponavljanje(vector<int>& data, const int& n, vector<int>& sljedeci_indeks) {
	int element;
	for (int i = 0; i < n; i++) {
		element = data.at(i);
		sljedeci_indeks.at(element)++;
		ispisi_sljedeci_indeks(sljedeci_indeks);
	}
}

void pretvori_ponavljanje_u_indekse(vector<int>& sljedeci_indeks, const int& n) {
	sljedeci_indeks.at(0)--;
	for (int i = 1; i < n; i++) {
		sljedeci_indeks.at(i) += sljedeci_indeks.at(static_cast<int64_t>(i) - 1);
	}
}

void prepisi_u_sortirano(vector<int>& data, const int& n, vector<int>& sljedeci_indeks, vector<int>& sortirano) {
	for (int i = n - 1; i >= 0; i--) {
		int element = data.at(i);
		int stavi_na_indeks = sljedeci_indeks.at(element)--;
		sortirano.at(stavi_na_indeks) = element;
	}
}

void prekopiraj(vector<int>& sortirano, const int& n, vector<int>& data) {
	for (int i = 0; i < n; i++) {
		data.at(i) = sortirano.at(i);
	}
}

void counting_sort(vector<int>& data, const int& n) {
	// Pronalazak najveceg elementa.
	int max = max_element(data, n);

	// Priprema polja za cuvanje podataka o broju ponavljanja i indeksima na koje doðu sortirani elementi.
	vector<int> sljedeci_indeks = napravi_polje(max + 1);

	// Pomocno polje koje ce sadrzavati sortirane podatke.
	vector<int> sortirano = napravi_polje(n);

	// Brojanje ponavljanja.
	prebroji_ponavljanje(data, n, sljedeci_indeks);

	// Pretvaranje broja pojavljivanja u indekse sortiranog polja. Trenutno nam sljedeci_indeks sadržava BROJ PONAVLJANJA, a nakon petlje æe sadržavati INDEKSE u sortiranom polju.
	pretvori_ponavljanje_u_indekse(sljedeci_indeks, max + 1);

	// Smještanje elemenata u sortirano polje na izraèunate indekse.
	prepisi_u_sortirano(data, n, sljedeci_indeks, sortirano);

	// Kopiranje iz pomoænog u glavno.
	prekopiraj(sortirano, n, data);

	vector<int>().swap(sljedeci_indeks);
	vector<int>().swap(sortirano);
}

