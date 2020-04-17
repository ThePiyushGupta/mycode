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
class graphNode {
public:
	// data
	vi adj, wt;
	int dist;
	graphNode() {
		dist = 0;
	}
};

class graph {
public:
	// data values
	int n;
	vector<graphNode> nd;
	vector<vi> dist;
	// multiset<pi, greater<pi>> s;
	multiset<int, greater<int>> s;
	// functions
	graph(int nodeNumber) {
		n = nodeNumber + 1;
		nd.resize(n);
		// dist.resize(n, vi(n, INT_MAX / 2));
	}

	void addEdge(int a, int b, bool weighted = false, int weight = 0) {
		nd[a].adj.pb(b);
		nd[b].adj.pb(a);
		if (weighted) {
			dist[a][b] = dist[b][a] = weight;
			nd[a].wt.pb(weight);
			nd[b].wt.pb(weight);
		}
	}

	void filldist(int itr, int par, int val) {
		nd[itr].dist = val;
		for (auto it : nd[itr].adj) {
			if (it == par) continue;
			filldist(it, itr, val + 1);
		}
	}

	int fillbeh(int itr, int par) {
		// nd[itr].dist = val;
		// EVARS(adj[itr]);
		int beh = 0;
		for (auto it : nd[itr].adj) {
			if (it == par) continue;
			beh += fillbeh(it, itr);
		}
		// s.insert({val, itr});
		// nd[itr].beh = beh;
		// EVARS(itr, par);
		s.insert(nd[itr].dist - beh);
		return beh + 1;
	}

	void solve(int kw) {
		// EVARS(k);
		filldist(1, 0, 0);
		// EVARS(k);

		fillbeh(1, 0);
		EVARS(s.size());

		// for (auto it : nd) {
		// 	EVARS(it.dist, it.beh);
		// }

		ll res = 0;
		while (kw--) {
			// EVARS(res, kw);

			auto k = *s.begin();
			// EVARS(res, kw);

			s.erase(s.begin());
			// EVARS(res, kw);
			res += k;

			// ll val = k.F;
			// ll beh = n + 10 - k.S;
			// res += val * (beh + 1) - beh;
			// EVARS(res, kw);
		}
		cout << res << endl;
	}
};
int main() {
	dragonforce();
	int n;
	cin >> n >> k;
	graph myg(n);

	for (int c = 0; c < n - 1; ++c) {
		int g, h;
		cin >> g >> h;
		myg.addEdge(g, h);
	}

	myg.solve(k);
}