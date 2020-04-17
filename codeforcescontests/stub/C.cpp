#include <bits/stdc++.h>
//*****************************************************************************************************
using namespace std;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<string> vs;
typedef vector<vector<int>> vii;
//*****************************************************************************************************
vector<string> split(const string &s, char c) {
	vector<string> v;
	stringstream ss(s);
	string x;
	while (getline(ss, x, c))
		v.emplace_back(x);
	return move(v);
}
template <typename T, typename... Args>
inline string arrStr(T arr, int n) {
	stringstream s;
	s << "[";
	for (int i = 0; i < n - 1; i++)
		s << arr[i] << ",";
	s << arr[n - 1] << "]";
	return s.str();
}

#if !defined(ONLINE_JUDGE)
#define EVARS(args...)       \
	__evars_begin(__LINE__); \
	__evars(split(#args, ',').begin(), args);
#else
#define EVARS(args...)
#endif	// DEBUG
inline void __evars_begin(int line) {
	cerr << "#" << line << ": ";
}
template <typename T>
inline void __evars_out_var(vector<T> val) { cerr << arrStr(val, val.size()); }
template <typename T>
inline void __evars_out_var(T *val) { cerr << arrStr(val, 10); }
template <typename T>
inline void __evars_out_var(T val) { cerr << val; }
inline void __evars(vector<string>::iterator it) { cerr << endl; }

template <typename T, typename... Args>
inline void __evars(vector<string>::iterator it, T a, Args... args) {
	cerr << it->substr((*it)[0] == ' ', it->length()) << "=";
	__evars_out_var(a);
	cerr << "; ";
	__evars(++it, args...);
}
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
#define mem(a, x) memset(a, x, sizeof(a))
#define mnv(v) *min_element(v.begin(), v.end())
#define mxv(v) *max_element(v.begin(), v.end())
#define pr(x) cout << fixed << setprecision(x);
#define N 100005
int r, c, n, k, m;	//predeclared control variables for loops
//************************************************************************************************************
int solve() {
	int n;
	vi a(3);
	input(a);

	// multiset<pi> ms;
	vector<pi> idk;

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < a[r]; c++) {
			cin >> k;
			idk.push_back({k, r});
		}
	}

	sort(all(idk));

	vector<vector<ll>> b(3);
	for (auto it : idk) {
		if (!sz(b[it.S]))
			b[it.S].pb(it.F);
		else if (b[it.S].back() != it.F)
			b[it.S].pb(it.F);
	}
	EVARS(b[0], b[1], b[2]);

	ll res = LLONG_MAX;
	for (auto it : b[0]) {
		int g = lower_bound(b[1].begin(), b[1].end(), it) - b[1].begin() - 1;
		// int gm = upper_bound(b[1].begin(), b[1].end(), it) - b[1].begin();
		int h = lower_bound(b[2].begin(), b[2].end(), it) - b[2].begin() - 1;
		// int hm = upper_bound(b[2].begin(), b[2].end(), it) - b[2].begin();

		if (g < 0) g++;
		if (h < 0) h++;
		EVARS(g, h, it);
		for (int r = g; r < g + 2 && r < b[1].size(); r++) {
			for (int c = h; c < h + 2 && c < b[2].size(); c++) {
				ll k = (it - b[1][r]) * (it - b[1][r]) +
					   (it - b[2][c]) * (it - b[2][c]) +
					   (b[2][c] - b[1][r]) * (b[2][c] - b[1][r]);
				res = min(res, k);
			}
		}
	}
	swap(b[0], b[1]);
	for (auto it : b[0]) {
		int g = lower_bound(b[1].begin(), b[1].end(), it) - b[1].begin() - 1;
		// int gm = upper_bound(b[1].begin(), b[1].end(), it) - b[1].begin();
		int h = lower_bound(b[2].begin(), b[2].end(), it) - b[2].begin() - 1;
		// int hm = upper_bound(b[2].begin(), b[2].end(), it) - b[2].begin();

		if (g < 0) g++;
		if (h < 0) h++;
		EVARS(g, h, it);
		for (int r = g; r < g + 2 && r < b[1].size(); r++) {
			for (int c = h; c < h + 2 && c < b[2].size(); c++) {
				ll k = (it - b[1][r]) * (it - b[1][r]) +
					   (it - b[2][c]) * (it - b[2][c]) +
					   (b[2][c] - b[1][r]) * (b[2][c] - b[1][r]);
				res = min(res, k);
			}
		}
	}

	swap(b[0], b[2]);
	for (auto it : b[0]) {
		int g = lower_bound(b[1].begin(), b[1].end(), it) - b[1].begin() - 1;
		// int gm = upper_bound(b[1].begin(), b[1].end(), it) - b[1].begin();
		int h = lower_bound(b[2].begin(), b[2].end(), it) - b[2].begin() - 1;
		// int hm = upper_bound(b[2].begin(), b[2].end(), it) - b[2].begin();

		if (g < 0) g++;
		if (h < 0) h++;
		EVARS(g, h, it);
		for (int r = g; r < g + 2 && r < b[1].size(); r++) {
			for (int c = h; c < h + 2 && c < b[2].size(); c++) {
				ll k = (it - b[1][r]) * (it - b[1][r]) +
					   (it - b[2][c]) * (it - b[2][c]) +
					   (b[2][c] - b[1][r]) * (b[2][c] - b[1][r]);
				res = min(res, k);
			}
		}
	}

	cout << res << endl;
	EVARS(res);
	return 0;
}

int main() {
	dragonforce();
	test() {
		solve();
	}
}