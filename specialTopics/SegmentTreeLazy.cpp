#include <bits/stdc++.h>
using namespace std;

class SegmentTreeLazy {
public:
	int n;
	vector<int> t, pd;
	SegmentTreeLazy(vector<int> &a) {
		n = a.size();
		t.resize(4 * n), pd.resize(4 * n);
		build(a, 1, 0, n - 1);
	}

	int merge(int a, int b) {
		// change as per requirements
		return a + b;
	}

	void build(vector<int> &a, int v, int tl, int tr) {
		if (tl == tr) {
			// change as per requirements
			t[v] = t[tl];
		} else {
			int tm = (tl + tr) / 2;
			build(a, 2 * v, tl, tm);
			build(a, v * 2 + 1, tm + 1, tr);
			t[v] = merge(t[2 * v], t[2 * v + 1]);
		}
	}

	void push(int v, int tl, int tr) {
		if (tl != tr) {
			pd[2 * v] += pd[v];
			pd[2 * v + 1] += pd[v];
		}
		t[v] += (tr - tl + 1) * pd[v];
		pd[v] = 0;
	}

	// increase all values by add
	void update(int v, int tl, int tr, int l, int r, int add) {
		if (l > r) return;
		if (l == tl && r == tr) {
			pd[v] += add;
			push(v, tl, tr);
		} else {
			int tm = (tl + tr) / 2;
			push(v, tl, tr);
			update(2 * v, tl, tm, l, min(tm, r), add);
			update(2 * v + 1, tm + 1, tr, max(tm + 1, l), r, add);
			t[v] = merge(t[2 * v], t[2 * v + 1]);
		}
	}

	int query(int v, int tl, int tr, int l, int r) {
		if (l > r) return 0;

		push(v, tl, tr);

		if (tl == l && tr == r) {
			return t[v];
		} else {
			int tm = (tl + tr) / 2;
			return merge(
				query(2 * v, tl, tm, l, min(tm, r)),
				query(2 * v + 1, tm + 1, tr, max(tm + 1, l), r));
		}
	}
};