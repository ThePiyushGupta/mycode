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
    int b[] = {4, 8, 15, 16, 23, 42};

    vi a(6);
    cout << "? 1 1" << endl;
    cin >> a[0];
    a[0] = sqrt(a[0]);
    cout << "? 2 2" << endl;
    cin >> a[1];
    a[1] = sqrt(a[1]);

    ll p = 4 * 8 * 15 * 16 * 23 * 42;
    p /= a[0] * a[1];

    int w, x, y, z;
    cout << "? 3 4" << endl;
    cin >> n;
    w = n;
    x = p / n;

    cout << "? 3 5" << endl;
    cin >> n;
    y = n;
    z = p / n;

    int e[] = {5, 7, 23};
    for (int c = 0; c < 3; c++)
    {
        if (w % e[c] == 0 && y % e[c] == 0)
        {
            int res;
            switch (e[c])
            {
            case 5:
                res = 15;
                break;

            case 7:
                res = 42;
                break;

            case 23:
                res = 23;
                break;
            }

            a[2] = res;
            a[3] = w / res;
            a[4] = y / res;
            a[5] = x / a[4];
            break;
        }

        if (w % e[c] == 0 && z % e[c] == 0)
        {
            int res;
            switch (e[c])
            {
            case 5:
                res = 15;
                break;

            case 7:
                res = 42;
                break;

            case 23:
                res = 23;
                break;
            }

            a[2] = w / res;
            a[3] = res;
            a[4] = y / a[2];
            a[5] = z / res;
            break;
        }

        if (x % e[c] == 0 && y % e[c] == 0)
        {
            int res;
            switch (e[c])
            {
            case 5:
                res = 15;
                break;

            case 7:
                res = 42;
                break;

            case 23:
                res = 23;
                break;
            }

            a[2] = y / res;
            a[3] = w / a[2];
            a[4] = res;
            a[5] = x / res;
            break;
        }

        if (x % e[c] == 0 && z % e[c] == 0)
        {
            int res;
            switch (e[c])
            {
            case 5:
                res = 15;
                break;

            case 7:
                res = 42;
                break;

            case 23:
                res = 23;
                break;
            }

            a[3] = z / res;
            a[2] = w / a[3];
            a[4] = x / res;
            a[5] = res;
            break;
        }
    }
    cout << "! ";
    for (int c = 0; c < 6; c++)
    {
        cout << a[c] << ' ';
    }
}