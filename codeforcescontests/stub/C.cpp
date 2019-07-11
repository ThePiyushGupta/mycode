// using adjancency list
#include <bits/stdc++.h>
#define sz(a) a.size()
#define pb push_back
using namespace std;
typedef pair<int, int> pi;
typedef vector<int> vi;
#define dragonforce()                 \
	ios_base::sync_with_stdio(false); \
	cin.tie(NULL);                    \
	cout.tie(NULL);                   \
	cerr.tie(NULL);

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
		visited[p] = true, q.push(p);
		while (!q.empty()) {
			int itr = q.front();
			q.pop();
			for (int i = 0; i < sz(nodes[itr].adj); i++) {
				auto pt = nodes[itr].adj[i];
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
		for (int i = 0; i < sz(nodes[itr].adj); i++) {
			if (!visited[nodes[itr].adj[i]])
				dfsUtil(nodes[itr].adj[i], visited);
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

		for (int i = 0; i < sz(nodes[itr].adj); i++) {
			if (!visited[nodes[itr].adj[i]])
				topologicalSortUtil(nodes[itr].adj[i], visited, res);
		}

		res.pb(itr);
	}

	void dijkstra(int root) {
		vi dist(n, 100000000);
		vi visited(n);
		int r = 0;
		priority_queue<pi, vector<pi>, greater<pi>> minHeap;

		minHeap.push({0, root});
		dist[root] = 0;
		int mx = 0, ct = 0;

		while (!minHeap.empty() && r < n - 1) {
			int u = minHeap.top().second;
			if (!visited[u]) {
				if (mx < minHeap.top().first) {
					mx = minHeap.top().first;
					ct = 1;
				} else if (mx == minHeap.top().first)
					ct++;
				r++;
			}
			visited[u] = 1;
			minHeap.pop();

			for (int i = 0; i < sz(nodes[u].adj); ++i) {
				if (dist[nodes[u].adj[i]] > dist[u] + nodes[u].wt[i]) {
					dist[nodes[u].adj[i]] = dist[u] + nodes[u].wt[i];
					minHeap.push({dist[nodes[u].adj[i]], nodes[u].adj[i]});
				}
			}
		}
		cout << mx << ' ' << ct << endl;
	}
};

int main() {
	dragonforce();
	int n, m, q;
	cin >> n >> m >> q;
	graph mygraph(n);
	for (int c = 0; c < m; c++) {
		int a, b, f;
		cin >> a >> b >> f;
		mygraph.addEdge(a, b, true, f);
	}
	while (q--) {
		int a;
		cin >> a;
		mygraph.dijkstra(a);
	}
}