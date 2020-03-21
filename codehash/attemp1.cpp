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
#define by(x) [](const auto &a, const auto &b) { return a.x > b.x; }
#define grsort() [](const auto &a, const auto &b) { return a > b; }
#define F first
#define S second
#define mem(a, x) memset(a, x, sizeof(a))
#define mnv(v) *min_element(v.begin(), v.end())
#define mxv(v) *max_element(v.begin(), v.end())
#define pr(x) cout << fixed << setprecision(x);
#define N 100005
#define alpha 23
#define beta 4
#define gamma 0.1
int r, c, n, k, m;  //predeclared control variables for loops
//************************************************************************************************************
// bool comp()(const auto &a, const auto &b) { return a > b; }
int nb, nl, nd;
float sumbooks = 0;

float findscore(float a, float b, float c) {
	return alpha * (a / sumbooks) - beta * (b / (float(nd))) + gamma / c;
}

class lib {
public:
	int n, m, t, id;
	vector<int> b;
	lib(int _n, int _t, int _m, vi &_b, int _id) {
		n = _n, t = _t, m = _m, b = _b, id = _id;
	}
};

int main() {
	dragonforce();
	cin >> nb >> nl >> nd;
	vi books(nb);

	input(books);
	for (int c = 0; c < nb; c++) {
		sumbooks += books[c];
	}
	vi ld(nl), lm(nl);
	vector<vi> libbook(nl);
	// EVARS(nb, nl, nd, books);
	vector<lib> libarr;
	vector<pair<float, lib>> idk;
	vi visited(nb);

	for (int c = 0; c < nl; c++) {
		cin >> k >> ld[c] >> lm[c];
		for (int r = 0; r < k; r++) {
			cin >> m;
			libbook[c].pb(m);
		}
		lib temp(k, ld[c], lm[c], libbook[c], c);
		libarr.pb(temp);
		ll tempscore = 0;
		for (auto it : libbook[c]) {
			if (visited[it]) continue;
			visited[it] = 1;
			tempscore += books[it];
		}

		idk.pb({findscore(tempscore, ld[c], lm[c]), temp});
		// idk.pb((ld[c], temp));
		// EVARS(libbook[c]);
	}
	sort(all(idk), by(F));
	// reverse(all(idk));

	fill(all(visited), 0);
	int day = 0;
	ll score = 0;
	vi liboutid;
	vector<vi> liboutv;
	for (auto itr : idk) {
		lib temp = itr.S;
		vector<pi> bid;
		// EVARS(itr.F)
		for (int c = 0; c < temp.n; c++) {
			bid.pb({books[temp.b[c]], temp.b[c]});
		}
		day += temp.t;
		// EVARS(day, nd);
		sort(all(bid), by(F));
		int ct = 0;
		vi vtemp;
		for (int c = day + 1; c < nd && ct < temp.n; c++) {
			for (int r = 0; r < temp.m && ct < temp.n; r++, ct++) {
				// EVARS(c, r, ct)
				if (visited[bid[ct].S]) {
					r--;
					continue;
				}
				visited[bid[ct].S] = 1;
				score += bid[ct].F;
				vtemp.pb(bid[ct].S);
			}
		}
		if (vtemp.size()) {
			liboutid.pb(temp.id);
			liboutv.pb(vtemp);
		} else {
			day -= temp.t;
		}
	}
	// EVARS(liboutid);
	cout << sz(liboutid) << endl;
	for (int c = 0; c < sz(liboutid); c++) {
		cout << liboutid[c] << ' ' << liboutv[c].size() << endl;
		for (auto it : liboutv[c]) cout << it << ' ';
		cout << endl;
	}
	EVARS(score);
}