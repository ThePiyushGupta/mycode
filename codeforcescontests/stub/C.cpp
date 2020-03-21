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
#endif  // DEBUG
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
int r, c, n, k, m;  //predeclared control variables for loops
//************************************************************************************************************

// int P[SIZE * 2];

// Transform S into new string with special characters inserted.
string convertToNewString(const string &s) {
	string newString = "@";

	for (int i = 0; i < s.size(); i++) {
		newString += "#" + s.substr(i, 1);
	}

	newString += "#$";
	return newString;
}

string longestPalindromeSubstring(const string &s) {
	string Q = convertToNewString(s);
	int c = 0, r = 0;  // current center, right limit
	vi P(Q.size() + 10);
	// EVARS(Q);

	for (int i = 1; i < Q.size() - 1; i++) {
		// find the corresponding letter in the palidrome subString
		int iMirror = c - (i - c);

		if (r > i) {
			P[i] = min(r - i, P[iMirror]);
		}

		// expanding around center i
		while (Q[i + 1 + P[i]] == Q[i - 1 - P[i]]) {
			P[i]++;
		}

		// Update c,r in case if the palindrome centered at i expands past r,
		if (i + P[i] > r) {
			c = i;  // next center = i
			r = i + P[i];
		}
	}

	// Find the longest palindrome length in p.

	int maxPalindrome = 0;
	int centerIndex = 0;
	// EVARS(P, s);

	for (int i = 1; i < Q.size() - 1; i++) {
		// &&(centerIndex - maxPalindrome == 1 || max)
		if (P[i] > maxPalindrome && (i - P[i] - 1) / 2 == 0) {
			maxPalindrome = P[i];
			centerIndex = i;
		}
	}

	// cout << maxPalindrome << "\n";
	return s.substr((centerIndex - 1 - maxPalindrome) / 2, maxPalindrome);
}

int main() {
	dragonforce();
	test() {
		string s, pre, suf, temp, res;
		cin >> s;
		n = sz(s);
		int ct = 0;
		while (ct < n / 2) {
			if (s[ct] == s[n - ct - 1]) {
				pre += s[ct];
			} else
				break;
			ct++;
		}
		suf = pre;
		reverse(all(suf));
		temp = s.substr(ct, n - 2 * ct);
		// EVARS(temp, pre, suf, longestPalindromeSubstring(temp));
		string pretemp = longestPalindromeSubstring(temp), suftemp = temp;
		reverse(all(suftemp));
		suftemp = longestPalindromeSubstring(suftemp);
		reverse(all(suftemp));
		EVARS(temp, pre, suf, pretemp, suftemp);

		if (ln(pretemp) > ln(suftemp)) {
			res = pre + pretemp + suf;
		} else
			res = pre + suftemp + suf;
		cout << res << endl;
	}
}