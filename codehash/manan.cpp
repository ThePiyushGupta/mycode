//#define DEBUG
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

// #include <>
// #include <iostream>

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace std;

using namespace std;

#define BSET(a, p) ((a) | (1ll << (p)))
#define BCHK(a, p) ((a) & (1ll << (p)))
#define BXOR(a, p) ((a) ^ (1ll << (p)));
#define BREM(a, p) (BCHK(a, p) ? (BXOR(a, p)) : (a))
#define BSHO(a, N) (bitset<N>(a))

#define fi first
#define sc second
#define pb push_back

#ifdef DEBUG
#define dbg(s) \
	{ s; }
#define PRELUDE
#endif

#ifndef DEBUG
#define PRELUDE                       \
	{                                 \
		ios ::sync_with_stdio(false); \
		cin.tie(0);                   \
		cout.tie(0);                  \
	}
#define dbg(s)
#define endl "\n"
#endif

//#define int ll
#define i32 int32_t

#define RBTTYPE int
#define ordered_set tree<RBTTYPE, null_type, less<RBTTYPE>, rb_tree_tag, tree_order_statistics_node_update>
// Ordered set docs:
// order_of_key (k) : Number of items strictly smaller than k .
// find_by_order(k) : K-th element in a set (counting from zero).

#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int alpha = 1;
const int beta = 1;
const int gama = 10;
const int delta = 5;
const int rho = 1000;

// To remove randomization use 0 below:
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// inline int ri(int x) { // from [0, n-1]
//     return uniform_int_distribution<int>(0, x - 1)(rng);
// }

// inline ld rf() { // from [0, 1]
//     return uniform_real_distribution<ld>(0, 1)(rng);
// }

ll gcd(ll x, ll y) {
	if (x < y) return gcd(y, x);
	if (y == 0) return x;
	return gcd(y, x % y);
}

const ll mod = 1e9 + 7;

ll modexp(ll x, ll ex) {
	ll ans = 1ll;
	while (ex > 0) {
		if (ex & 1ll) ans = (ans * x) % mod;
		ex >>= 1ll;
		x = (x * x) % mod;
	}
	return ans;
}

const int maxn = 1e5 + 7;

const ll inf = 1e8;

int b, l, d;
int scores[maxn];
int reg[maxn];
int ships[maxn];
vector<int> books[maxn];

int curscore;
bool used[maxn];
vector<pii> libs;
vector<vector<int> > ans;

void addLib(int idx) {
	if (reg[idx] < 0)
		return;
	int days = d - reg[idx];
	int maxBooks = days * ships[idx];
	if (maxBooks <= 0)
		return;
	vector<int> sc;
	for (ll i = 0; i < books[idx].size(); i++) {
		int x = books[idx][i];
		if (used[x])
			continue;
		sc.pb(scores[x]);
	}
	sort(all(sc));
	// sort(all(sc));
	reverse(all(sc));
	int maxi = 0;
	int sum = 0;
	int g = sc.size();
	g = min(g, maxBooks);
	for (int i = 0; i < g; i++) {
		maxi = max(maxi, sc[i]);
		sum += sc[i];
	}
	int median = sc[g / 2];
	if (sum == 0)
		return;
	int avg = sum / reg[idx];
	int scorex = alpha * maxi + beta * sum + gama * avg + delta * median - rho * reg[idx];
	pii z = make_pair(scorex, idx);
	libs.pb(z);
}

int findMax() {
	int x = libs[0].sc;
	int cur = libs[0].fi;

	for (int i = 1; i < libs.size(); i++) {
		if (cur < libs[i].fi) {
			cur = libs[i].fi;
			x = libs[i].sc;
		}
	}

	return x;
}

void relaxLibrary(int idx) {
	int days = d - reg[idx];
	d -= reg[idx];
	reg[idx] = -1;

	int maxBooks = days * ships[idx];
	vector<pii> sc;
	for (ll i = 0; i < books[idx].size(); i++) {
		int x = books[idx][i];
		if (used[x])
			continue;
		pii z = make_pair(scores[x], x);
		sc.pb(z);
	}
	sort(all(sc));
	reverse(all(sc));
	int g = sc.size();
	g = min(g, maxBooks);
	vector<int> xz;
	xz.pb(idx);
	xz.pb(g);
	ans.pb(xz);
	xz.clear();
	int sum = 0;
	for (int i = 0; i < g; i++) {
		xz.pb(sc[i].sc);
		used[sc[i].sc] = true;
		sum += sc[i].fi;
	}
	curscore += sum;
	ans.pb(xz);
}

void solve() {
	//Input
	cin >> b >> l >> d;
	for (int i = 0; i < b; i++) {
		cin >> scores[i];
	}

	int n, x;
	for (int i = 0; i < l; i++) {
		cin >> n >> reg[i] >> ships[i];
		for (int j = 0; j < n; j++) {
			cin >> x;
			books[i].pb(x);
		}
	}
	dbg(cout << "inputEnd" << endl;);
	//Heuristic Start
	memset(used, false, sizeof(used));
	//curscore = 0;
	int libidx;
	while (true) {
		dbg(cout << "New Iteration" << endl;);
		libs.clear();
		for (int i = 0; i < l; i++) {
			addLib(i);
		}
		if (libs.size() == 0)
			break;
		libidx = findMax();
		//curscore+=libs[libidx].fi;
		relaxLibrary(libidx);
	}
	// cout<<curscore<<endl;
	ofstream outfile;
	outfile.open("scores.txt", ios::app);
	outfile << curscore << endl;
	outfile.close();

	n = ans.size();
	n /= 2;
	cout << n << endl;
	for (int i = 0; i < ans.size(); i++)
	// for(auto x: ans)
	{
		for (int j = 0; j < ans[i].size(); j++)
		// for(auto y:x)
		{
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
}

i32 main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output_f.txt", "w", stdout);

	PRELUDE;
	int t = 1;
	//cin>>t;
	while (t--)
		solve();
}
