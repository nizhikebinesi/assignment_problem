// Copyright (c) 2017 Denis Skripov
// https://github.com/nizhikebinesi/assignment_problem
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <algorithm>

using namespace std;

#define ZERO 0LL

struct Identifier {
	size_t id_of_line;
	vector<size_t> id_of_zeros;
	Identifier(size_t i) : id_of_line(i) {};
};

struct Element {
	long long key;
	bool is_colored,
		is_cross_out_in_line,
		is_cross_out_in_column,
		is_cross_out_in_column_and_line,
		is_counted;
};

struct CmpClass {
	bool operator() (const Element &i, const Element &j) {
		return i.key < j.key;
	}
} cmp;

struct CmpByCountOfZeros {
	bool operator() (const Identifier &i, const Identifier &j) {
		return i.id_of_zeros.size() < j.id_of_zeros.size();
	}
} z_cmp;

struct Matrix {
	vector<vector<Element>> matr;
	vector<Identifier> zeros_in_line;
	//vector<vector<Identifier>> zeros_in_line;
	// vector<vector<size_t>> zeros_in_line;
	// vector<size_t> count_of_zeros_in_column, 
	//	count_of_zeros_in_line;
	vector<size_t> cross_or_colored_line;
	vector<bool> cross_column;
	size_t size;
};

void hungarian_very_slow(Matrix c) {
	// step #1
	for (size_t i = 0; i < c.size; i++) {
		long long min = 
			(c.matr[i][min_element(c.matr.begin(), c.matr.end(), cmp).operator*]).key;
		for (size_t j = 0; j < c.size; j++) {
			c.matr[i][j].key -= min;
			if (!c.matr[i][j].is_counted && c.matr[i][j].key == ZERO) {
				c.zeros_in_line[i].id_of_zeros.push_back(j);
				// c.zeros_in_line[i].push_back(Identifier(i, j));
				// c.zeros_in_line[i].push_back(j);
				// c.count_of_zeros_in_line[i]++;
				c.matr[i][j].is_counted = true;
			}
		}
	}
	// step #2
	for (size_t i = 0; i < c.size; i++) {
		long long min = c.matr[0][i].key;
		for (size_t j = 0; j < c.size; j++) {
			if (min > c.matr[j][i].key) {
				min = c.matr[j][i].key;
			}
		}
		for (size_t j = 0; j < c.size; j++) {
			c.matr[j][i].key -= min;
			if (!c.matr[j][i].is_counted && c.matr[j][i].key == ZERO) {
				c.zeros_in_line[j].id_of_zeros.push_back(i);
				// c.zeros_in_line[j].push_back(Identifier(j, i));
				// c.zeros_in_line[j].push_back(i);
				// c.count_of_zeros_in_line[j]++;
				c.matr[j][i].is_counted = true;
			}
		}
	}

	// step #3
	size_t k = 0;
	while (k != c.size) {
		for (size_t i = 0; i < c.size; i++) {
			for (size_t j = 0; j < c.zeros_in_line.size(); j++) {
				sort(c.zeros_in_line[j].id_of_zeros.begin(), 
					c.zeros_in_line[j].id_of_zeros.end());
			}
			sort(c.zeros_in_line.begin(), c.zeros_in_line.end(), z_cmp);
			for (size_t j = 0; j < c.size; j++) {
				
				//if (c.zeros_in_line[j].size() == ZERO) {
				if (c.zeros_in_line[j].id_of_zeros.size() == ZERO) {
					continue;
				}

				c.matr[j][c.zeros_in_line[j].id_of_zeros[0]].is_colored = true;

				for (size_t k = 1; k < c.zeros_in_line[j].id_of_zeros.size(); k++) {

				}
			}
			/*size_t id =
				*min_element(c.count_of_zeros_in_line.begin(),
					c.count_of_zeros_in_line.end());*/
			
		}
	}
}

/*void hungarian_very_slow(vector<vector<long long>> c) {
	int size = c.size();
	vector<unsigned long long> columns, lines;
	bool is_column = false; // column -> true , line -> false
	while (true) {
		// step #1
		for (size_t i = 0; i < size; i++) {
			long long min_ = *min_element(c[i].begin(), c[i].end());
			for (size_t j = 0; j < size; j++) {
				c[i][j] -= min_;
			}
		}
		// step #2
		for (size_t i = 0; i < size; i++) {
			long long min_ = c[0][i];
			for (size_t j = 0; j < size; j++) {
				if (min_ > c[j][i]) {
					min_ = c[j][i];
				}
			}
			for (size_t j = 0; j < size; j++) {
				c[j][i] -= min_;
			}
		}
		// step #3

	}
}*/

int main(void) {

}