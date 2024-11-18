#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void addEdge(vector<vector<int>> &g, int src, int dest) {
    g[src].push_back(dest);
    g[dest].push_back(src);
}

void print(const vector<vector<int>> &g) {
    for (int i = 0; i < g.size(); i++) {
        cout << i << ": ";
        for (int j : g[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

void bfs(const vector<vector<int>> &g, int s) {
    int n = g.size();
    vector<bool> visited(n, false);
    queue<int> q;
    visited[s] = true;
    q.push(s);
    cout << "OUTPUT FOR BFS" << endl;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";
        for (int adj : g[curr]) {
            if (!visited[adj]) {
                visited[adj] = true;
                q.push(adj);
            }
        }
    }
    cout << endl;
}

void solveDFS(const vector<vector<int>> &g, int s, vector<bool> &visited) {
    visited[s] = true;
    cout << s << " ";
    for (int adj : g[s]) {
        if (!visited[adj]) {
            solveDFS(g, adj, visited);
        }
    }
}

void dfs(const vector<vector<int>> &g, int s) {
    vector<bool> visited(g.size(), false);
    cout << "OUTPUT FOR DFS" << endl;
    solveDFS(g, s, visited);
}

int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;
    vector<vector<int>> g(n);
    cout << "Enter the number of edges: ";
    int e;
    cin >> e;
    cout << "Enter the edges (src dest) separated by space:" << endl;
    for (int i = 0; i < e; i++) {
        int src, dest;
        cin >> src >> dest;
        if (src >= 0 && src < n && dest >= 0 && dest < n) {
            addEdge(g, src, dest);
        } else {
            cout << "Invalid edge. Please enter nodes between 0 and " << n - 1 << "." << endl;
            i--;
        }
    }
    print(g);
    cout << "Give start node from 0 to " << n - 1 << ": ";
    int s;
    cin >> s;
    if (s < 0 || s >= n) {
        cout << "Invalid start node." << endl;
    } else {
        cout << "CHOOSE:\n1 FOR BFS\n2 FOR DFS" << endl;
        int opt;
        cin >> opt;
        if (opt == 1) {
            bfs(g, s);
        } else if (opt == 2) {
            dfs(g, s);
        } else {
            cout << "Invalid option." << endl;
        }
    }
    return 0;
}
