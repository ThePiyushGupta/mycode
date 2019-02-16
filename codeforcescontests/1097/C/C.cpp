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
inline void __evars_begin(int line) { cout << "#" << line << ": "; }
template <typename T>
inline void __evars_out_var(vector<T> val) {
    cout << arrStr(val, val.size());
}
template <typename T>
inline void __evars_out_var(T *val) {
    cout << arrStr(val, 10);
}
template <typename T>
inline void __evars_out_var(T val) {
    cout << val;
}
inline void __evars(vector<string>::iterator it) { cout << endl; }

template <typename T, typename... Args>
inline void __evars(vector<string>::iterator it, T a, Args... args) {
    cout << it->substr((*it)[0] == ' ', it->length()) << "=";
    __evars_out_var(a);
    cout << "; ";
    __evars(++it, args...);
}
//*****************************************************************************************************
#define debug(x) \
    { cout << #x << " = " << x << endl; }
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
    cout.tie(NULL);
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

int main() {
    dragonforce();
    int n;
    cin >> n;

    vector<int> a;
    string str;

    for (int cr = 0; cr < n; cr++) {
    here:
        cin >> str;
        int cta = 0,ctb=0;
        for (c = 0; c < str.length(); c++) {
            if (str[c] == '(') {
                cta++;
            } else if (str[c] == ')'&&cta>0)    cta--;
            else ctb--;
        }

        if(cta==0&&ctb==0||ctb==0){
            a.pb(cta);
        }
        else if(cta==0){
            a.pb(ctb);
        }

    }

    sort(all(a));
    EVARS(a);
    int st = 0, en = sz(a) - 1;
    int res = 0;
    while (st < en) {
        EVARS(a[st], a[en]);
        if (a[en] == (-1 * a[st])) {
            res++;
            en--;
            st++;
        } else if (a[en] > (-1 * a[st]))
            en--;
        else
            st++;
    }
    cout << res << endl;
}