#include <bits/stdc++.h>
//*****************************************************************************************************
using namespace std;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<string> vs;
//*****************************************************************************************************
#define debug(x)                          \
	{                                     \
		cerr << #x << " = " << x << endl; \
	}
#define mod 1000000007
#define MAX 20000000
#define test()   \
	long long o; \
	cin >> o;    \
	while (o--)
#define input(vec) for (unsigned int c = 0; c<vec.size(); cin>> vec[c++])
#define output(vec, x)                                                 \
	{                                                                  \
		for (unsigned int c = 0; c < vec.size(); x << vec[c++] << ' ') \
			;                                                          \
		x << endl;                                                     \
	}
#define sz(k) k.size()
#define ln(s) s.length()
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define finc(i, x, y) for (__typeof(x) i = x; i < y; i++)
#define fdec(i, x, y) for (__typeof(x) i = x; i > y; i--)
#define fincp(itr, x) for (__typeof(x.begin()) itr = x.begin(); itr != x.end(); itr++)
#define fdecp(itr, x) for (auto itr = x.end() - 1; itr != x.begin() - 1; itr--)
#define dragonforce()                 \
	ios_base::sync_with_stdio(false); \
	cin.tie(NULL);                    \
	cout.tie(NULL);                   \
	cerr.tie(NULL);
#define PI (acos(-1.0))
#define E 2.71828182845904523536
#define by(x) [](const auto &a, const auto &b) { return a.x < b.x; }
#define grsort() [](const auto &a, const auto &b) { return a > b; }
#define F first
#define S second
#define mnv(v) *min_element(v.begin(), v.end())
#define mxv(v) *max_element(v.begin(), v.end())
#define pr(x) cout << fixed << setprecision(x);
int r, c, n, k;	 //predeclared control variables for loops
#define N 50005
//************************************************************************************************************
//                                                GSS1 Spoj
// ************************************************************************************************************
struct nodeseg {
	int val, lmax, rmax, sum;

	void fill(int k) {
		sum = lmax = rmax = val = k;
	}

	void merge(nodeseg a, nodeseg b) {
		lmax = max(a.lmax, a.sum + b.lmax);
		rmax = max(b.rmax, b.sum + a.rmax);
		sum = a.sum + b.sum;
		val = max(max(lmax, rmax), max(a.val, b.val));
		val = max(val, a.rmax + b.lmax);
	}
};
nodeseg refs, segtree[N << 1];
// vector<nodeseg> segtree;
void build() {
	for (int c = n - 1; c > 0; c--) {
		segtree[c].merge(segtree[c << 1], segtree[((c << 1) | 1)]);
	}
}

int querys(int l, int r) {
	nodeseg lft, rght;
	lft = rght = refs;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l & 1) lft.merge(lft, segtree[l++]);
		if (r & 1) rght.merge(segtree[--r], rght);
	}
	lft.merge(lft, rght);
	return lft.val;
}

void modify(int pos, int val) {
	segtree[pos += n].fill(val);
	while (pos >= 1)
		segtree[pos].merge(segtree[pos << 1], segtree[(pos << 1) + 1]);
}

class asdf {
public:
	const int k;
	asdf(int z) : k(z) {
	}
};

int main() {
	dragonforce();
	cin >> n >> k;
	vector<int> a(k + 1);
	for (int c = 0; c < n; c++) {
		cin >> r;
		a[r]++;
	}
	k = n;
	int res = 0, left = 0;
	for (int c = 0; c < n; c++) {
		res += (a[c] / 2) * 2;
		a[c] %= 2;
		if (a[c]) left++;
	}

	res += (left + 1) / 2;
	cout << res;
}