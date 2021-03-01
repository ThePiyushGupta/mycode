#include <bits/stdc++.h>

#include "constants.h"

// #define GRPCT
using namespace std;

int main() {
	// generate tasks and dependencies
	// id ,depends on

	srand(time(0));
	vector<int> sz;
	for (int c = 0; c < GRPCT; ++c) {
		sz.push_back(2 + rand() % MAXGRPSZ);
	}

	int id = 0;
	ofstream myfile;
	myfile.open("AppsData.txt");
	myfile << GRPCT << endl;
	int ct = 0;
	for (int c = 0; c < GRPCT; ++c) {
		myfile << sz[c] << ' ';
		ct += sz[c];
	}
	myfile << endl
		   << ct << endl;

	default_random_engine generator;
	poisson_distribution<int> distribution(5);

	for (int r = 0; r < GRPCT; ++r) {
		for (int c = 0; c < sz[r]; ++c) {
			// print id and dependencies
			int dc = 0;
			// int k = rand() % 1100;
			// if (k < 300)
			// 	dc = 3;
			// else if (k < 800)
			// 	dc = 2;
			// else if (k < 1000)
			// 	dc = 1;
			// else
			// 	dc = 0;

			dc = distribution(generator);

			// if (c == 0) dc = 0;
			// cerr << dc << ' ';
			dc %= (c + 1);

			myfile << id++ << ' ' << dc << ' ';

			for (int i = 0; i < dc; ++i) {
				myfile << rand() % c + id - c - 1 << ' ';
			}
			myfile << endl;
		}
	}
}