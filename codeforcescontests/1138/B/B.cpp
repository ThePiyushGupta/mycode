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
    int n;
    cin >> n;

    string a, b;
    cin >> a >> b;

    vi no, ac, cl, bo;
    for (int c = 0; c < n; c++)
    {
        if (a[c] == '0' && b[c] == '0')
        {
            no.push_back(c);
        }
        if (a[c] == '0' && b[c] == '1')
        {
            cl.push_back(c);
        }
        if (a[c] == '1' && b[c] == '0')
        {
            ac.push_back(c);
        }
        if (a[c] == '1' && b[c] == '1')
        {
            bo.push_back(c);
        }
    }

    if (sz(bo) % 2 == 1 && sz(ac) + sz(cl) == 0 || sz(cl) > n / 2 || sz(ac) > n / 2)
    {
        return cout << -1, 0;
    }

    while (sz(bo) && sz(cl) > sz(ac))
    {
        ac.push_back(bo[sz(bo) - 1]);
        bo.pop_back();
    }

    while (sz(ac) > sz(cl) && sz(bo))
    {
        cl.push_back(bo[sz(bo) - 1]);
        bo.pop_back();
    }
    int o = sz(cl) - sz(ac);
    EVARS(ac);
    while (sz(ac) > sz(cl))
    {
        ac.pop_back();
    }
    while (o > 0)
    {
        ac.push_back(cl[sz(cl) - 1]);
        cl.pop_back();
        o--;
    }
    EVARS(ac);
    while (sz(bo) > 1)
    {
        ac.push_back(bo[sz(bo) - 1]);
        bo.pop_back();
        cl.push_back(bo[sz(bo) - 1]);
        bo.pop_back();
    }
    reverse(all(ac));

    EVARS(ac);
    if (sz(bo))
    {
        ac.push_back(cl[0]);
    }

    while (sz(ac) < n / 2)
    {
        ac.push_back(no[sz(no) - 1]);
        no.pop_back();
    }
    if (sz(ac) > n / 2)
        return cout << -1, 0;

    for (int c = 0; c < n / 2; c++)
    {
        cout << ac[c] + 1 << ' ';
    }
}