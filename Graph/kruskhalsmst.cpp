// using adjancency list
#include <queue>
#include <vector>
#include <algorithm>
#define sz(a) a.size()
#define pb push_back
using namespace std;
typedef pair<int, int> pi;
typedef vector<int> vi;

class graph
{
  public:
    vector<pair<int, pi>> edges, mstedges;

    int n, e;

    graph(int _n, int _e)
    {
        n = _n;
        e = _e;
    }

    void addedges(int a, int b, int w)
    {
        edges.pb({w, {a, b}});
    }

    void mst()
    {
        sort(edges.begin(), edges.end());
        disjointsets dset(n);

        int res = 0;

        for (auto it : edges)
        {
            int u = it.second.first, v = it.second.second;
            int setu = dset.find(u), setv = dset.find(v);

            if (setu != setv)
            {
                mstedges.pb(it);

                dset.merge(setu, setv);
            }
        }
    }

    class disjointsets
    {
      public:
        vi par, rnk;
        int n;

        disjointsets(int _n)
        {
            n = _n;
            par.resize(n + 1);
            rnk.resize(n + 1);

            //set every element as parent of itself
            for (int c = 0; c < n; c++)
            {
                par[c] = c;
            }
        }

        //find parent of child
        int find(int child)
        {

            if (child != par[child])
            {
                par[child] = find(par[child]);
            }
            return par[child];
        }

        void merge(int x, int y)
        {
            x = find(x);
            y = find(y);

            //make tree with smaller height a sub tree of the other tree
            if (rnk[x] > rnk[y])
            {
                par[y] = x;
            }
            else
                par[x] = y;

            if (rnk[x] == rnk[y])
                rnk[y]++;
        }
    };

};
(((())))