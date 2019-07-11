#include <bits/stdc++.h>
using namespace std;
vector<bool> a(100000000, true);

// function to generate sieve of erasthatos
// input : int n
void gensieve(int n) {
	a.resize(n + 10, false);
	a[0] = a[1] = false;
	for (int c = 4; c < n; c += 2) {
		a[c] = false;
	}
	// vector <int> res;
	// res.push_back(2);
	int k = sqrt(n);
	for (int c = 3; c <= k; c += 2) {
		if (a[c]) {
			// res.push_back(c);

			for (long long r = c * 1ll * c; r < n; r += c) {
				a[r] = false;
			}
		}
	}
}
