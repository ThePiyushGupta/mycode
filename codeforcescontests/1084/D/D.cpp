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
stack<int> st;
vi wt;
vector<vi> conn;
vector<vi> connlen;
vi par;
vector <ll> res;
ll dfs()
{
    int pos = st.top();
    st.pop();
    // int retvalue = 0;
    ll max1 = 0, max2 = 0;
    EVARS(conn[pos]);
    for (int c = 0; c < sz(conn[pos]); c++) {
        if (conn[pos][c] == par[pos])
            continue;
        // EVARS(conn[pos][c]);
        st.push(conn[pos][c]);
        par[conn[pos][c]]=pos;
        ll k = dfs() - connlen[pos][c];
        k = (k > 0) ? k : 0;

        if (k > max1) {
            max2 = max1;
            max1 = k;
        } else if (k > max2)
            max2 = k;
    }
    res[pos]=max1+max2+wt[pos];
    return max1+wt[pos];
}

int main()
{
    dragonforce();
    cin >> n;
    wt.pb(0);
    conn.pb(vi(0));
    connlen.pb(vi(0));

    for (c = 1; c < n+1; c++) {
        wt.pb(get());
        conn.pb(vi(0));
        connlen.pb(vi(0));
    }
    par.resize(n+1, 0);
    int len, na, nb;
    for (c = 0; c < n - 1; c++) {
        cin >> na >> nb >> len;
        conn[na].pb(nb);
        connlen[na].pb(len);
        conn[nb].pb(na);
        connlen[nb].pb(len);
    }
    res.resize(n+1, 0);
    // vi par(n);
    //input obtained
    st.push(1);
    EVARS(wt);
    dfs();
    cout<<mxv(res);
}