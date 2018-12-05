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

template <class t = int>
t getinteractive()
{
    fflush(stdout);
    t a;
    cin >> a;
    return a;
}

//************************************************************************************************************
ll f, g;
int readval(ll a, ll b)
{
    cout << "? " << a << ' ' << b << endl;
    int retval = getinteractive<int>();
    return retval;
    // cerr << (a ^ f)<<' '<<(b^g)<<endl;
    // if ((a ^ f) > (b ^ g)) {
    //     return 1;
    // } else if ((a ^ f) < (b ^ g)) {
    //     return -1;
    // } else {
    //     return 0;
    // }
}

int main()
{
    dragonforce();
    ll a = 0, b = 0;
    // cin >> f >> g;
    vi place(30);
    place[0] = 1;
    for (size_t i = 1; i < 30; i++) {
        place[i] = place[i - 1] * 2;
    }

    int dig = 29;
    ll prev, next;
    bool decider = false, exit = false;
    while (dig >= 0) {
        if (decider) {
            next = readval(a + place[dig], b + place[dig]);
            if (exit == false) {
                if (next < 0) {
                    a += place[dig];
                } else {
                    b += place[dig];
                }
                dig--;
                exit = true;
            }
            // EVARS(next, prev);
            else {
                if (prev * next < 0) {

                    if (next > 0) {
                        b += place[dig];
                    } else {
                        a += place[dig];
                    }
                    decider = false;
                    exit=false;
                    dig--;

                } else if (prev * next > 0) {
                    {
                        next = readval(a, b + place[dig]);
                        EVARS(next,a,b);
                        if (next > 0) {
                            a += place[dig];
                            b += place[dig];
                        }
                        dig--;
                    }
                } else
                    decider = false;
    
            }

        } else {

            prev = readval(a + place[dig], b);
            next = readval(a, b + place[dig]);
            EVARS(prev, next);
            if (prev * next < 0) {

                if (next > 0) {
                    a += place[dig];
                    b += place[dig];
                }
                dig--;
            } else if (prev * next == 0) {
                if(exit==false){
                    decider=true;
                    continue;
                }
                if (prev == 0) {
                    a += place[dig];
                } else {
                    b += place[dig];
                }
                dig--;

            } else {
                decider = true;
            }
        }
    }
    cout << "! " << a << ' ' << b;
}