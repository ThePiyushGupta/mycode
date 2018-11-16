// using adjancency list
#include <queue>
#include <vector>
using namespace std;
class graphNode {
   private:
    /* data */
    // 0 to n based on our implementaiton
    int key;
    // add in the rest of the data
    vector<int> connections;
    int col;

   public:
    graphNode(int k) {
        // insert other data
        insert();
        key = k;
        col = 0;
    }

    // function to insert other data
    void insert() {}

    void addConnecitons(int t) { connections.push_back(t); }

    void delConnections(int t) {
        //
    }

    friend class graph;
};

class graph {
   private:
    int n;
    vector<graphNode> node;

   public:
    graph(int nodeNumber = t) {
        n = t;
        // obtain and add n number of nodes from the user
    }

    // use a queue for the purpose of bfs
    void bfs(int p) {
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

    void dfs(int t) {
        vector<int> visited(n);
        for (size_t i = 0; i < n; i++) {
            if (!visited[i]) dfsUtil(i, &visited);
        }
    }

    void dfsUtil(int itr, vector<int> &visited) {
        visited[itr] = 1;

        for (size_t i = 0; i < node[itr].connections.size(); i++) {
            if (!visited[node[itr].connections[i]])
                dfsUtil(node[itr].connections[i],visited);
        }

        visited[itr] = 2;
    }
    ~graph() {}
};