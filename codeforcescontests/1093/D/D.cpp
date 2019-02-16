#include <bits/stdc++.h>
//*****************************************************************************************************
using namespace std;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<string> vs;
//*****************************************************************************************************
vector<string> split(const string& s, char c)
{
    vector<string> v;
    stringstream ss(s);
    string x;
    while (getline(ss, x, c))
        v.emplace_back(x);
    return move(v);
}
template <typename T, typename... Args>
inline string arrStr(T arr, int n)
{
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
#endif // DEBUG
inline void __evars_begin(int line)
{
    cerr << "#" << line << ": ";
}
template <typename T>
inline void __evars_out_var(vector<T> val) { cerr << arrStr(val, val.size()); }
template <typename T>
inline void __evars_out_var(T* val) { cerr << arrStr(val, 10); }
template <typename T>
inline void __evars_out_var(T val) { cerr << val; }
inline void __evars(vector<string>::iterator it) { cerr << endl; }

template <typename T, typename... Args>
inline void __evars(vector<string>::iterator it, T a, Args... args)
{
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
#define by(x) [](const auto& a, const auto& b) { return a.x < b.x; }
#define grsort() [](const auto& a, const auto& b) { return a > b; }
#define F first
#define S second
#define mem(a, x) memset(a, x, sizeof(a))
#define mnv(v) *min_element(v.begin(), v.end())
#define mxv(v) *max_element(v.begin(), v.end())
#define pr(x) cout << fixed << setprecision(x);
template <class t = int>
t get()
{
    t a;
    std::cin >> a;
    return a;
}
int r, c, n, k; //predeclared control variables for loops
//************************************************************************************************************
vector<ll> powr;

class graphNode {
public:
    //data
    vi adj, wt;
    int a;

    graphNode()
    {
        a = 0;
    }
};

class graph {
public:
    //data values
    int n;
    vector<graphNode> nodes;

    //functions
    graph(int nodeNumber)
    {
        n = nodeNumber;
        nodes.resize(n + 1);
    }

    void addEdge(int a, int b, bool weighted = false, int weight = 0)
    {
        nodes[a].adj.pb(b);
        nodes[b].adj.pb(a);
        if (weighted) {
            nodes[a].wt.pb(weight);
            nodes[b].wt.pb(weight);
        }
    }

    ll findans()
    {
        vector<bool> visited(n + 1, false);
        vi col(n + 1);
        vi grcol(3);
        grcol[1] = 1;
        ll res = 1;
        for (c = 1; c < n + 1; c++) {
            if (!visited[c]) {
                col[c] = 1;
                if (!bfs(c, col, visited, grcol)) {
                    return 0;
                } else {
                    res = (res * (powr[grcol[1]] + powr[grcol[2]])) % 998244353;
                }
                grcol[2] = 0;
                grcol[1] = 1;
            }
        }
        return res;
    }

    bool bfs(int p, vi& col, vector<bool>& visited, vi& grcol)
    {
        queue<int> q;
        visited[p] = true;
        q.push(p);
        while (!q.empty()) {
            int itr = q.front();
            q.pop();
            int chcol = (col[itr] == 2) ? 1 : 2;
            for (int i = 0; i < sz(nodes[itr].adj); i++) {
                
                k = nodes[itr].adj[i];
                if (col[k] == 0 || col[k] == chcol) {
                    if (col[k] == 0) {
                        col[k] = chcol;
                        grcol[chcol]++;
                    }
                } else
                    return false;
                    
                if (!visited[nodes[itr].adj[i]]) {
                    visited[k] = true;
                    q.push(k);
                }
            }
        }
        return true;
    }
};

int main()
{
    dragonforce();
    powr.resize(3 * 100000);
    ll k = 1;
    for (c = 0; c < 3 * 100000; c++) {
        powr[c] = k;
        k = (k * 2) % 998244353;
    }
    test()
    {
        int n, m;
        cin >> n >> m;
        graph mygraph(n);

        for (c = 0; c < m; c++) {
            mygraph.addEdge(get(), get());
        }

        cout << mygraph.findans() << endl;
    }
}