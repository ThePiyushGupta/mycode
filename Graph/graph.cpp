// using adjancency list
#include <queue>
#include <vector>
using namespace std;

class graphNode {
public:
    //data

    graphNode()
    {
    }
};

class graph {
private:
    int n;
    vector<graphNode> nodes;

public:
    graph(int nodeNumber)
    {
        n = nodeNumber;
        nodes.resize();
    }

    // use a queue for the purpose of bfs
    void bfs(int p)
    {
        queue<int> q;
        vector<bool> visited(n);
        q.push(p);
        while (!q.empty()) {
            int itr = q.front();
            q.pop();
            visited[itr] = true;

            for (size_t i = 0; i < node[itr].connections.size(); i++) {
                if (!visited[node[itr].connections[i]]) {
                    visited[node[itr].connections[i] = true;
                    q.push(node[itr].connections[i]);
                }
            }
        }
    }

    void dfs(int t)
    {
        vector<int> visited(n);
        for (size_t i = 0; i < n; i++) {
            if (!visited[i])
                dfsUtil(i, &visited);
        }
    }

    void dfsUtil(int itr, vector<int>& visited)
    {
        visited[itr] = 1;

        for (size_t i = 0; i < node[itr].connections.size(); i++) {
            if (!visited[node[itr].connections[i]])
                dfsUtil(node[itr].connections[i], visited);
        }

        visited[itr] = 2;
    }
    ~graph() {}
};