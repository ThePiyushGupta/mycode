#include <bits/stdc++.h>
#define pr(x) cout << fixed << setprecision(x);
using namespace std;

int main() {
	pr(2);
	for (int pos = 2; pos < 21; ++pos) {
		// int pos = 16;
		string inf = "output" + to_string(pos) + ".txt";
		ifstream fin(inf);
		double a, b, c, mx;
		fin >> a >> b >> c;
		cout << pos << " & " << c << " & ";
		mx = c;

		for (int i = 1; i < 10000; ++i) {
			fin >> a >> b >> c;
			mx = max(mx, c);
		}
		cout << c << " & " << mx << "\\\\" << endl;
	}
}