#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define finc(c, a, b) for (int c = a; c < b; ++c)
#define F first
#define S second
#define pi pair<int, int>
static auto fast = [] {ios_base::sync_with_stdio(false);cin.tie(nullptr);return 0; }();

class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		unordered_map<string, int> ct;
		for (auto it : words) ct[it]++;

		int len = words[0].size();
		vector<int> res;
		for (int r = 0; r < len; ++r) {
			unordered_map<string, int> seen;
			for (int beg = r, end = r; beg < s.size(); beg += len) {
				string temp = s.substr(beg, len);
				if (ct[temp] == 0) {
					seen.clear();
					continue;
					end = beg + len;
				}
				seen[temp]++;
				while (seen[temp] > ct[temp]) {
					string idk = s.substr(end, len);
					if (seen[idk]) seen[idk]--;
					end += len;
				}
				if (beg + len - end == words.size() * len) res.push_back(end);
			}
		}
		return res;
	}
};

vector<vi> adj, wt;
vector<vi> visited;

void dfs(int v, int d) {
	if (visited[v][d]) return;
	visited[v][d] = 1;
	for (int c = 0; c < adj[v].size(); ++c) {
		int k = d + wt[v][c];
		dfs(adj[v][c], k % 10);
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	visited.resize(n, vi(10));

	for (int c = 0; c < n; ++c) {
		int g, h, w;
		cin >> g >> h >> w;
		w %= 10;
		g--;
		h--;
		adj[g].push_back(h);
		adj[h].push_back(g);
		wt[g].push_back(w);
		wt[h].push_back((10 - w) % 10);
	}
}