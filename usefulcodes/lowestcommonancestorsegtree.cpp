#include <bits/stdc++.h>
//*****************************************************************************************************
using namespace std;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<string> vs;
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
#define mnv(v) *min_element(v.begin(), v.end())
#define mxv(v) *max_element(v.begin(), v.end())
#define pr(x) cout << fixed << setprecision(x);
int r, c, n, k;  //predeclared control variables for loops
#define N 50005
//************************************************************************************************************
vector<vi> adj, reft;
vi segarr, visited, mema, segtree, depth;

void dfsgen(int v, int par, int &ct) {
	depth[v] = depth[par] + 1;
	visited[v] = segarr.size();
	segarr.push_back(v);
	for (auto it : adj[v])
		if (it != par)
			dfsgen(it, v, ct), segarr.pb(v);
}

void buildseg(int pos, int beg, int end) {
	// EVARS(pos, beg, end);
	if (beg == end) {
		segtree[pos] = segarr[beg];
	} else {
		int mid = (beg + end) / 2;
		buildseg((pos << 1) + 1, beg, mid), buildseg((pos << 1) + 2, mid + 1, end);
		segtree[pos] = depth[segtree[(pos << 1) + 1]] < depth[segtree[(pos << 1) + 2]] ? segtree[(pos << 1) + 1] : segtree[(pos << 1) + 2];
	}
}

int LCAq(int qb, int qe, int b, int e, int pos) {
	if (b >= qb && e <= qe)
		return segtree[pos];
	else if (qb > e || qe < b)
		return 0;
	int mid = (b + e) / 2;
	int g = LCAq(qb, qe, b, mid, (pos << 1) + 1), h = LCAq(qb, qe, mid + 1, e, (pos << 1) + 2);
	// EVARS(g, h);
	return depth[g] < depth[h] ? g : h;
}

int main() {
	dragonforce();
	r = 0;
	test() {
		cin >> n;
		vi &a = visited;
		segtree = a = mema, adj = reft, adj.resize(n + 1), a.resize(n + 1), depth.resize(n + 1);
		for (int c = 0; c < n; c++) {
			test() {
				cin >> k;
				adj[c + 1].push_back(k), a[k] = true;
			}
		}
		for (int c = 0; c < n; c++)
			if (a[c + 1] == false) {
				k = c + 1;
				break;
			}

		fill(all(visited), false);
		int ct = 0;
		depth[0] = 0;
		// EVARS(k);
		dfsgen(k, 0, ct);
		EVARS(segarr);
		EVARS(visited);
		segtree.resize(sz(segarr) << 2);

		buildseg(0, 0, sz(segarr) - 1);
		EVARS(segtree);
		depth[0] = INT_MAX;
		cout << "Case " << ++r << ":\n";
		test() {
			int g, h;
			cin >> g >> h;
			g = visited[g], h = visited[h];
			EVARS(g, h);
			cout << LCAq(min(g, h), max(g, h), 0, sz(segarr) - 1, 0) << endl;
		}
	}
}