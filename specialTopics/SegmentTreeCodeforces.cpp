#include <bits/stdc++.h>

using namespace std;

// this is an iterativer implementation of a segment tree
// space requirement = 2n
class SegmentTree {
	int n;
	vector<int> t;
	SegmentTree(vector<int> &a) {
		int n = a.size();
		t.resize(n + 1);
		build();
	}

	int merge(int a, int b) {
		return a + b;
	}

	void build() {
		for (int c = n - 1; c > 0; c--) {
			t[c] = merge(t[c * 2], t[c * 2 + 1]);
		}
	}
	// query in range [l,r)
	int query(int l, int r) {
		int res = 0;
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l & 1) res = merge(t[l++], res);
			if (r & 1) res = merge(res, t[--r]);
		}
		return res;
	}

	// set val at pos
	int modify(int pos, int val) {
		for (t[pos += n] = val; pos > 1; pos /= 2) {
			t[pos / 2] = merge(t[pos], t[pos ^ 1]);
		}
	}
};