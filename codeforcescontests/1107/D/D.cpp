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
int r,c,n,k;//predeclared control variables for loops
//************************************************************************************************************
void HexToBin(string,int []);
int main()
{
    dragonforce();
    int n;
    cin>>n;
    EVARS(n);
    int a[n][n];
    for(int c = 0; c < n; c++){
        string s;
        cin>>s;
        EVARS(a[c])
        HexToBin(s,a[c]);
        EVARS(a[c]);
    }


    vi h(n,INT_MAX),v(n,INT_MAX);
    int ct=1;
    EVARS(n);
    for(c = 0; c < n; c++){
        ct=1;
        for(r = 1; r < n; r++){
            if(a[c][r]==a[c][r-1])
                ct++;
            else{
                h[c]=min(h[c],ct);
                ct=1;
            }
        }
    }
    for(c = 0; c < n; c++){
        ct=1;
        for(r = 1; r < n; r++){
            if(a[r][c]==a[r-1][c])
                ct++;
            else{
                v[c]=min(v[c],ct);
                ct=1;
            }
        }
    }
    EVARS(h,v);
    int k=min(mnv(v),mnv(h));

    cout<<gcd(k,n);
    


}

void HexToBin(string hexdec,int a[]) 
{ 
    long int i = 0; 
    int ct=0;
    string num;
    while (hexdec[i]) { 
  
        switch (hexdec[i]) { 
        case '0': 
            num="0000"; 
            break; 
        case '1': 
            num="0001"; 
            break; 
        case '2': 
            num="0010"; 
            break; 
        case '3': 
            num="0011"; 
            break; 
        case '4': 
            num="0100"; 
            break; 
        case '5': 
            num="0101"; 
            break; 
        case '6': 
            num="0110"; 
            break; 
        case '7': 
            num="0111"; 
            break; 
        case '8': 
            num="1000"; 
            break; 
        case '9': 
            num="1001"; 
            break; 
        case 'A': 
        case 'a': 
            num="1010"; 
            break; 
        case 'B': 
        case 'b': 
            num="1011"; 
            break; 
        case 'C': 
        case 'c': 
            num="1100"; 
            break; 
        case 'D': 
        case 'd': 
            num="1101"; 
            break; 
        case 'E': 
        case 'e': 
            num="1110"; 
            break; 
        case 'F': 
        case 'f': 
            num="1111"; 
            break; 
        } 
        for(int c = 0; c < 4; c++){
            a[ct++]=num[c]-'0';
        }
        i++; 
    } 
} 