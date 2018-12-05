#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define debug(x)                          \
    {                                     \
        cerr << #x << " = " << x << endl; \
    }
// #define mod             1000000007
#define MAX 20000000
#define test()   \
    long long o; \
    cin >> o;    \
    while (o--)
#define input(vec) for (unsigned int c = 0; c<vec.size(); cin>> vec[c++])
#define output(vec, x)                                             \
    for (unsigned int c = 0; c < vec.size(); x << vec[c++] << ' ') \
        ;                                                          \
    x << endl;
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
// #define PI              (acos(-1.0))
// #define E               2.71828182845904523536
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

using namespace std;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<string> vs;

int main()
{
    vi a;
    ll k = 1;
    for (size_t i = 0; i < 30; i++) {
        a.pb(k);
        k *= 2;
    }

    int c = 0, b = 0;
    int dig = 30;
    int d, f;
    bool und = false;

    while (dig >= 0) {
        if (!und) {
            cout << "? " << c + a[dig] << ' ' << b;
            fflush(stdout);
            cin >> d;
            cout << "? " << c << ' ' << b + a[dig];
            fflush(stdout);
            cin >> f;

            if (f * d < 0) {
                if (d == -1) {
                    c += a[dig];
                    b += a[dig];
                }
                dig--;
            } else {
                und = true;
            }
        } else {
            int prev = d;
            cout << "? " << c << ' ' << b;
            fflush(stdout);
            cin >> d;
            if (d == 1) {
                c += a[dig--];
            } else if (d == -1) {
                b += a[dig--];
            } else {
            }

            if (prev > 1) {
                cout << "? " << c + a[dig] << ' ' << b;
                fflush(stdout);
                cin >> f;
                if(f>1)
            }
        }
    }
}