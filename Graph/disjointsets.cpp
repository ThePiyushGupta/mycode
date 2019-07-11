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
#define mem(a, x) memset(a, x, sizeof(a))
#define mnv(v) *min_element(v.begin(), v.end())
#define mxv(v) *max_element(v.begin(), v.end())
#define pr(x) cout << fixed << setprecision(x);
template <class t = int>
t get() {
	t a;
	std::cin >> a;
	return a;
}
int r, c, n, k;  //predeclared control variables for loops
//************************************************************************************************************

class unnode {
private:
	/* data */
public:
	int parent, height, val;
	unnode() {
		// val = n;
		height = 1;
	}
};
class disjointsets {
private:
	/* data */
public:
	int n;
	vector<unnode> nodes;
	multiset<int> s;
	disjointsets(int val) {
		n = val + 1;
		nodes.resize(n);
		s.clear();
		// s.insert(2);
		// cout << *s.rbegin() - *s.begin() << endl;

		for (int c = 1; c < n; c++) {
			s.insert(1);
			nodes[c].parent = nodes[c].val = c;
		}
		// cout << *s.rbegin() - *s.begin() << endl;
	}

	int find(int i) {
		if (i == nodes[i].parent)
			return i;
		else
			return nodes[i].parent = find(nodes[i].parent);
	}

	void setunion(int a, int b) {
		a = find(a);
		b = find(b);
		int mx = 1;
		if (a != b) {
			if (nodes[b].height > nodes[a].height)
				swap(a, b);
			nodes[b].parent = a;
			s.erase(s.find(nodes[a].height));
			s.erase(s.find(nodes[b].height));
			nodes[a].height += nodes[b].height;
			s.insert(nodes[a].height);
		}
		cout << *s.rbegin() - *s.begin() << endl;
	}
};

int main() {
	dragonforce();
	int n;
	cin >> n;
	disjointsets dj(n);
	test() {
		int a, b;
		cin >> a >> b;
		dj.setunion(a, b);
	}
}