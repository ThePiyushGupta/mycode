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
#define mod 998244353
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
inline ll solve(int n, int ls, set<pi> &s) {
	EVARS(n, ls);
	int rst = 0, lst = ls, rs = n - ls;
	while (lst + rst <= n) {
		s.insert({lst++, rst++});
	}
	rst = rs, lst = 0;
	while (lst + rst <= n) {
		s.insert({lst++, rst++});
	}
	return 0;
}

int power(int x, int y, int p) {
	int res = 1;  // Initialize result

	x = x % p;	// Update x if it is more than or
				// equal to p

	while (y > 0) {
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res * x) % p;

		// y must be even now
		y = y >> 1;	 // y = y/2
		x = (x * x) % p;
	}
	return res;
}

// Returns n^(-1) mod p
int modInverse(int n, int p) {
	return power(n, p - 2, p);
}

// Returns nCr % p using Fermat's little
// theorem.
int nCrModPFermat(int n, int r, int p) {
	// Base case
	if (r == 0)
		return 1;

	// Fill factorial array so that we
	// can find all factorial of r, n
	// and n-r
	int fac[n + 1];
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % p;

	return (fac[n] * modInverse(fac[r], p) % p *
			modInverse(fac[n - r], p) % p) %
		   p;
}
int nCrModp(int n, int r, int p) {
	// Optimization for the cases when r is large
	if (r > n - r)
		r = n - r;

	// The array C is going to store last row of
	// pascal triangle at the end. And last entry
	// of last row is nCr
	int C[r + 1];
	memset(C, 0, sizeof(C));

	C[0] = 1;  // Top row of Pascal Triangle

	// One by constructs remaining rows of Pascal
	// Triangle from top to bottom
	for (int i = 1; i <= n; i++) {
		// Fill entries of current row using previous
		// row values
		for (int j = min(i, r); j > 0; j--)

			// nCj = (n-1)Cj + (n-1)C(j-1);
			C[j] = (C[j] + C[j - 1]) % p;
	}
	return C[r];
}
int main() {
	dragonforce();
	string s, t;
	cin >> s >> t;
	ll res = 0;
	set<pi> st;
	for (int c = 1; c <= s.size(); ++c) {
		s = s.substr(1, n - 1) + s[0];
		EVARS(s);
		if (s.substr(0, t.size()) != t) continue;
		solve(s.size(), c, st);
	}

	for (auto it : st) {
		EVARS(it.F, it.S, res)
		res += nCrModp(it.S + it.F, it.S, 998244353);
		res %= mod;
		// EVARS(res);
	}
	cout << res << endl;
}