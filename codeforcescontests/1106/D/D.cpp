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
class graphNode {
   public:
    // data
    vi adj, wt;

    graphNode() {}
};

class graph {
   public:
    // data values
    int n;
    vector<graphNode> nodes;

    // functions
    graph(int nodeNumber) {
        n = nodeNumber + 1;
        nodes.resize(n);
    }

    void addEdge(int a, int b, bool weighted = false, int weight = 0) {
        nodes[a].adj.pb(b);
        nodes[b].adj.pb(a);
        if (weighted) {
            nodes[a].wt.pb(weight);
            nodes[b].wt.pb(weight);
        }
    }

    // add a directed edge from a to b
    void addDirEdge(int a, int b, bool weighted = false, int weight = 0) {
        nodes[a].adj.pb(b);
        if (weighted) {
            nodes[a].wt.pb(weight);
        }
    }

    // use a queue for the purpose of bfs
    void bfs(int p) {
        queue<int> q;
        vector<bool> visited(n);
        visited[p] = true;
        q.push(p);
        while (!q.empty()) {
            int itr = q.front();
            q.pop();

            for (int i = 1; i < sz(nodes[itr].adj); i++) {
                auto pt = nodes[itr].adj[i];
                if (!visited[pt]) {
                    visited[pt] = true;
                    q.push(pt);
                }
            }
        }
    }

    void findans(){
        priority_queue <int, vector<int>, greater<int> > pq; 
        cout<<"1 ";
        vi visited(n,0);
        visited[1]=1;
        for(c = 0; c < nodes[1].adj.size(); c++){
            pq.push(nodes[1].adj[c]);
        }
        while(!pq.empty()){
            int k=pq.top();
            pq.pop();

            if(visited[k])
                continue;
            visited[k]=1;
            cout<<k<<' ';
                
            for(c = 0; c < nodes[k].adj.size(); c++){
                if(!visited[nodes[k].adj[c]])
                    pq.push(nodes[k].adj[c]);
            }
        }

    }

};

int main()
{
    dragonforce();
    int n,m;
    cin>>n>>m;

    graph mygraph(n);
    for(c = 0; c < m; c++){
        mygraph.addEdge(get(),get());
    }

    mygraph.findans();


}