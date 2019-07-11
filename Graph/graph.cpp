// using adjancency list
#include <bits/stdc++.h>
#define sz(a) a.size()
#define pb push_back
using namespace std;
typedef pair<int, int> pi;
typedef vector<int> vi;

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
	vector<graphNode> nd;
	vector<vi> dist;

	// functions
	graph(int nodeNumber) {
		n = nodeNumber + 1;
		nd.resize(n);
		dist.resize(n, vi(n, INT_MAX / 2));
	}

	void addEdge(int a, int b, bool weighted = false, int weight = 0) {
		nd[a].adj.pb(b);
		nd[b].adj.pb(a);
		if (weighted) {
			dist[a][b] = dist[b][a] = weight;
			nd[a].wt.pb(weight);
			nd[b].wt.pb(weight);
		}
	}

	// add a directed edge from a to b
	void addDirEdge(int a, int b, bool weighted = false, int weight = 0) {
		nd[a].adj.pb(b);
		if (weighted) {
			nd[a].wt.pb(weight);
		}
	}

	// use a queue for the purpose of bfs
	void bfs(int p) {
		queue<int> q;
		vector<bool> visited(n);
		visited[p] = true, q.push(p);
		while (!q.empty()) {
			int itr = q.front();
			q.pop();
			for (int i = 0; i < sz(nd[itr].adj); i++) {
				auto pt = nd[itr].adj[i];
				if (!visited[pt]) {
					visited[pt] = true, q.push(pt);
				}
			}
		}
	}

	void dfs(int t) {
		vector<int> visited(n);
		for (int i = 1; i < n; i++) {
			if (!visited[i]) dfsUtil(i, visited);
		}
	}

	void dfsUtil(int itr, vector<int>& visited) {
		visited[itr] = 1;
		for (int i = 0; i < sz(nd[itr].adj); i++) {
			if (!visited[nd[itr].adj[i]])
				dfsUtil(nd[itr].adj[i], visited);
		}
		visited[itr] = 2;
	}

	vi topologicalSort(int itr) {
		vi visited(n);
		vi res;
		topologicalSortUtil(itr, visited, res);
		return res;
	}

	void topologicalSortUtil(int itr, vi& visited, vi& res) {
		visited[itr] = 1;

		for (int i = 0; i < sz(nd[itr].adj); i++) {
			if (!visited[nd[itr].adj[i]])
				topologicalSortUtil(nd[itr].adj[i], visited, res);
		}

		res.pb(itr);
	}

	void dijkstra(int root) {
		vi dist(n, INT_MAX);
		priority_queue<pi, vector<pi>, greater<pi>> minHeap;
		// set <pi> pq; // wfen using sets

		minHeap.push({0, root});
		dist[root] = 0;

		while (!minHeap.empty()) {
			int u = minHeap.top().second;  // (*pq.begin()).second
			minHeap.pop();				   //pq.erase(pq.begin())

			for (int i = 0; i < sz(nd[u].adj); ++i) {
				if (dist[nd[u].adj[i]] > dist[u] + nd[u].wt[i]) {
					// if(dist[nd[u].adj[i]]!=INT_MAX){
					//     pq.erase({dist[nd[u].adj[i]],nd[u].adj[i]})
					// }
					dist[nd[u].adj[i]] = dist[u] + nd[u].wt[i];
					minHeap.push({dist[nd[u].adj[i]], nd[u].adj[i]});
					// pq.insert({dist[nd[u].adj[i]], nd[u].adj[i]});
				}
			}
		}
		//now we have shortest distances stored in dist
		for (auto&& i : dist) {
			cout << i << ' ';
		}
	}

	//Bellman Ford for single source shortest paths  , detects negative cycles

	// All pairs shortest paths
	// O(n3)
	void FloysWarshall() {
		// dp(u,v)[k] = dp[u,a][k-1]+ dp[a,v][k-1]
		for (int c = 0; c < n; c++) {
			dist[c][c] = 0;
		}
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++) {
				for (int c = 1; c < n; c++) {
					dist[i][j] = min(dist[i][j], dist[i][c] + dist[c][j]);
				}
			}
		}
	}
};

class dag {
private:
	/* data */
	// data values
	int n;
	vector<graphNode> nd;

public:
	dag(int nodeNumber) {
		n = nodeNumber + 1;
		nd.resize(n);
	}
	// add a directed edge from a to b
	void addDirEdge(int a, int b, bool weighted = false, int weight = 0) {
		nd[a].adj.pb(b);
		if (weighted) {
			nd[a].wt.pb(weight);
		}
	}

	void topsort() {
		vector<int> res;
	}
};
