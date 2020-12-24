#include <bits/stdc++.h>
using namespace std;

class dsu {
	vector<int> par;
	dsu(int n) {
		par.resize(n);
		for (int c = 0; c < n; ++c) par[c] = c;
	}
	int find_set(int v) {
		if (par[v] != v) par[v] = find_set(par[v]);
		return par[v];
	}
	int merge_set(int a, int b) {
		par[find_set(a)] = b;
	}
};