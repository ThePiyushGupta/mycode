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

#define EVARS(args...)                            \
    {                                             \
        __evars_begin(__LINE__);                  \
        __evars(split(#args, ',').begin(), args); \
    }

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
//************************************************************************************************************

class graphnode {
public:
    int key;
    vector<pi> connections;
    graphnode(int n)
    {
        key = n;
    }
    void addcon(int a, int w)
    {
        connections.pb({ a, w });
    }
};

class graph {
public:
    int n;
    vector<graphnode> nodes;

    graph(int _n)
    {
        n = _n;
        for (size_t i = 0; i < n; i++) {
            nodes.pb(graphnode(i + 1));
        }
    }

    void addedge(int a, int b, int w = 1)
    {
        nodes[a].addcon(b, w);
        nodes[b].addcon(a, w);
    }

    void dance(int k=1cp )
    {
        //do dfs from 1;
        //find number of vectices and number which are allowed.
        //output min
        vi visited(n);
        dfsUtil(k, visited);
        int ct=0;
        for(size_t i = 0; i < n; i++)
        {
            if(visited[i])
                ct++;
        }
        cout<<min(k,ct);
        
    }

    void dfsUtil(int itr, vector<int>& visited)
    {
        visited[itr-1] = 1;
        for (size_t i = 0; i < nodes[itr].connections.size(); i++) {
            if (!visited[nodes[itr].connections[i].F])
                dfsUtil(nodes[itr].connections[i].F, visited);
        }
        visited[itr-1] = 2;
    }
};
int main()
{
    dragonforce();
    int n, m, k;
    cin >> n >> m >> k;
    graph mygraph(n);

    for (size_t i = 0; i < m; i++) {
        mygraph.addedge(get(), get(), get());
    }

    mygraph.dance();
}