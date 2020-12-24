#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
public:
	int n;
	vector<int> t;

	SegmentTree(vector<int> a) {
		n = a.size();
		t.resize(4 * n);
		build(a, 1, 0, n - 1);
	}

	// change this function as per requirements
	int merge(int a, int b) {
		return a + b;
	}

	void build(vector<int> &a, int v, int tl, int tr) {
		if (tl == tr) {
			// change as per requirement
			t[v] = a[tl];
		} else {
			int tm = (tl + tr) / 2;
			build(a, v * 2, tl, tm);
			build(a, v * 2 + 1, tm + 1, tr);

			t[v] = merge(t[v * 2], t[v * 2 + 1]);
		}
	}

	// query in the range [l,r]
	int query(int v, int tl, int tr, int l, int r) {
		if (l > r)
			return 0;
		if (l == tl && r == tr) {
			return t[v];
		}

		int tm = (tl + tr) / 2;
		return merge(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
	}

	int query(int l, int r) {
		return query(1, 0, n - 1, l, r);
	}

	void update(int v, int tl, int tr, int pos, int new_val) {
		if (tl == tr) {
			// change this line as per requirements
			t[v] = new_val;
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				update(v * 2, tl, tm, pos, new_val);
			else
				update(v * 2 + 1, tm + 1, tr, pos, new_val);

			// change this line as per requirements
			t[v] = merge(t[v * 2], t[v * 2 + 1]);
		}
	}

	void update(int pos, int new_val) {
		update(1, 0, n - 1, pos, new_val);
	}
};