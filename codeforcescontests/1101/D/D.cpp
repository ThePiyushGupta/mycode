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
    while (getline(ss, x, c)) v.emplace_back(x);
    return move(v);
}
template <typename T, typename... Args>
inline string arrStr(T arr, int n) {
    stringstream s;
    s << "[";
    for (int i = 0; i < n - 1; i++) s << arr[i] << ",";
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
inline void __evars_begin(int line) { cerr << "#" << line << ": "; }
template <typename T>
inline void __evars_out_var(vector<T> val) {
    cerr << arrStr(val, val.size());
}
template <typename T>
inline void __evars_out_var(T *val) {
    cerr << arrStr(val, 10);
}
template <typename T>
inline void __evars_out_var(T val) {
    cerr << val;
}
inline void __evars(vector<string>::iterator it) { cerr << endl; }

template <typename T, typename... Args>
inline void __evars(vector<string>::iterator it, T a, Args... args) {
    cerr << it->substr((*it)[0] == ' ', it->length()) << "=";
    __evars_out_var(a);
    cerr << "; ";
    __evars(++it, args...);
}
//*****************************************************************************************************
#define debug(x) \
    { cerr << #x << " = " << x << endl; }
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
#define fincp(itr, x) \
    for (__typeof(x.begin()) itr = x.begin(); itr != x.end(); itr++)
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
int r, c, n, k;  // predeclared control variables for loops
//************************************************************************************************************
class graph {
   public:
    vector<pi> edges;

    int n, e;

    graph(int _n, int _e) {
        n = _n;
        e = _e;
    }

    void addedges(int a, int b) { edges.pb({a, b}); }

    void mst(vi &a) {
        sort(edges.begin(), edges.end());
        disjointsets dset(n);
        for (c = 1; c <= n; c++) {
            dset.gcdvec[c] = a[c-1];
        }

        for (auto it : edges) {
            int u = it.first, v = it.second;
            int setu = dset.find(u), setv = dset.find(v);
            if (__gcd(dset.gcdvec[setu], dset.gcdvec[setv]) > 1)
                dset.merge(setu, setv);
        }
        int res= mxv(dset.rnk);
        if(res==1&&mxv(a)==1)
            cout<<0;
        else cout<<res;
    }

    class disjointsets {
       public:
        vi par, rnk, gcdvec;
        int n;

        disjointsets(int _n) {
            n = _n;
            par.resize(n + 1);
            rnk.resize(n + 1, 1);
            gcdvec.resize(n + 1);

            for (int c = 0; c <= n; c++) {
                par[c] = c;
            }
        }

        // find parent of child
        int find(int child) {
            if (child != par[child]) {
                par[child] = find(par[child]);
            }
            return par[child];
        }

        void merge(int x, int y) {
            x = find(x);
            y = find(y);
            gcdvec[x] = gcdvec[y] = __gcd(gcdvec[x], gcdvec[y]);

            // make tree with smaller height a sub tree of the other tree
            if (rnk[x] > rnk[y]) {
                par[y] = x;
                rnk[x] += rnk[y];
            } else {
                par[x] = y;
                rnk[y] += rnk[x];
            }
        }
    };
};

int main() {
    dragonforce();
    int n;
    cin>>n;
    cout<<n<<endl;
    for(c = 0; c < n; c++){
        cout<<"1 ";
    }
}