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

    vector<vi> mat(n, vi(n));
    vi a(1005);
    for (c = 0; c < n * n; c++)
    {
        a[get()]++;
    }
    // EVARS(a);
    vi c2, c4, c1, c3;
    for (c = 0; c < 1005; c++)
    {
        if (a[c] >= 4)
            c4.push_back(c);
        if (a[c] % 4 == 2)
            c2.pb(c);
        if (a[c] % 4 == 1)
            c1.pb(c);
        if (a[c] % 4 == 3)
        {
            c2.pb(c);
            c1.push_back(c);
        }
    }
    // EVARS(c4);
    EVARS(7);

    for (size_t c = 0; c < n / 2; c++)
    {
        for (int i = 0; i < n / 2; i++)
        {
            if (c4.empty())
            {
                return cout << "NO", 0;
            }
            int k = c4[sz(c4) - 1];
            a[k] -= 4;
            if (a[k] < 4)
                c4.pop_back();

            mat[i][c] = mat[i][n-c-1] = mat[n - i - 1][c] = mat[n - i - 1][n - 1 - c] = k;
        }
    }

    // fill rows fill columns
    if (n & 1)
    {
        while (!c4.empty())
        {
            c2.push_back(c4[sz(c4) - 1]);
            c4.pop_back();
        }
        for (c = 0; c < n / 2; c++)
        {
            if (c2.empty())
            {
                return cout << "NO", 0;
            }
            int k = c2[sz(c2) - 1];

            a[k] -= 2;
            if (a[k] < 2)
                c2.pop_back();
            EVARS(k);
            mat[n / 2 ][c] = mat[n / 2 ][n - c - 1]=k;
            cerr << mat[n / 2][c] << mat[n / 2][n - c - 1] << k<<endl;
        }

        for (c = 0; c < n / 2; c++)
        {
            if (c2.empty())
            {
                return cout << "NO", 0;
            }
            int k = c2[sz(c2) - 1];
            a[k] -= 2;
            if (a[k] < 2)
                c2.pop_back();
            EVARS(k);
            mat[c][n / 2 ] = mat[n - c - 1][n / 2 ]=k;
        }

        if (c1.empty())
            return cout << "NO", 0;
        mat[n / 2 ][n / 2 ]=c1[0];
    }
    EVARS(7);
    cout<<"YES\n";
    for (c = 0; c < n; c++)
    {
        for (r = 0; r < n; r++)
        {
            cout << mat[c][r] << ' ';
        }
        cout << endl;
    }
}