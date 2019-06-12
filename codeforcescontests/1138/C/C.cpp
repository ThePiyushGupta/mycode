#include <bits/stdc++.h>
//*****************************************************************************************************
using namespace std;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<string> vs;
//*****************************************************************************************************
vector<string> split(const string &s, char c)
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
inline void __evars_out_var(T *val) { cerr << arrStr(val, 10); }
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
#define by(x) [](const auto &a, const auto &b) { return a.x < b.x; }
#define grsort() [](const auto &a, const auto &b) { return a > b; }
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

int main()
{
    dragonforce();
    int n, m;
    cin >> n >> m;

    vector<vi> a(n, vi(m)), v(n, vi(m)), h(n, vi(m));
    vi vmax(n), hmax(m);
    for (int c = 0; c < n; c++)
    {
        for (int r = 0; r < m; r++)
        {
            cin >> a[c][r];
        }
    }

    for (int c = 0; c < n; c++)
    {
        vector<pi> temp;
        for (int r = 0; r < m; r++)
        {
            temp.push_back({a[c][r], r});
        }
        sort(all(temp));
        int st = 1;
        v[c][temp[0].S] = 1;
        for (int r = 1; r < m; r++)
        {
            if (temp[r].F != temp[r - 1].F)
                st++;
            v[c][temp[r].S] = st;
        }
        EVARS(v[c]);
        vmax[c] = st;
    }
    for (int c = 0; c < m; c++)
    {
        vector<pi> temp;
        for (int r = 0; r < n; r++)
        {
            temp.push_back({a[r][c], r});
        }
        sort(all(temp));
        int st = 1;
        h[temp[0].S][c] = 1;
        for (int r = 1; r < n; r++)
        {
            if (temp[r].F != temp[r - 1].F)
                st++;
            h[temp[r].S][c] = st;
        }
        hmax[c] = st;
    }

    for (int c = 0; c < n; c++)
    {
        for (int r = 0; r < m; r++)
        {
            if (h[c][r] == v[c][r])
                cout << max(hmax[r], vmax[c]);
            else if (v[c][r] < h[c][r])
            {
                cout << max(hmax[r], vmax[c] + h[c][r] - v[c][r]);
            }
            else
            {
                cout << max(hmax[r] + v[c][r] - h[c][r], vmax[c]);
            }
            cout << ' ';
        }
        cout << endl;
    }

    return 0;
}