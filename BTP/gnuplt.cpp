#include <bits/stdc++.h>
using namespace std;

int main() {
	ifstream is;
	ofstream os;
	os.open("plotoutput.txt");

	for (int c = 2; c <= 20; ++c) {
		is.open("output" + to_string(c) + ".txt");

		int x;
		double cv, ns;

		while (is >> x >> cv >> ns)
			os << c << ' ' << x << ' ' << ns << endl;

		is.close();
	}
}