#include <iostream>
#include <vector>

using namespace std;

void addEdge(vector<vector<int>> &g, int src, int dest)
{
  g[src].push_back(dest);
  g[dest].push_back(src);
}

void print(vector<vector<int>> &g)
{
  for (int i = 0; i < g.size(); i++)
  {
    cout << i << ": ";
    for (int j : g[i])
    {
      cout << j << " ";
    }
    cout << endl;
  }
}

void deepdfs(vector<vector<int>> &g, int s, int depth, vector<bool> &visited)
{
  if (depth == 0)
    return;

  visited[s] = true;
  cout << s << " ";

  for (int adj : g[s])
  {
    if (!visited[adj])
    {
      deepdfs(g, adj, depth - 1, visited);
    }
  }
}

void iterativeDFS(vector<vector<int>> &g, int startNode, int maxDepth)
{
  for (int depth = 1; depth <= maxDepth; depth++)
  {
    cout << "DFS with depth " << depth << ": ";
    vector<bool> visited(g.size(), false);
    deepdfs(g, startNode, depth, visited);
    cout << endl;
  }
}

int main()
{
  int n = 21;
  vector<vector<int>> g(n);
  int e;
  cout << "Enter the number of edges: ";
  cin >> e;

  cout << "Enter the edges (src dest) separated by space:" << endl;
  for (int i = 0; i < e; i++)
  {
    int src, dest;
    cin >> src >> dest;
    if (src >= 0 && src < n && dest >= 0 && dest < n)
    {
      addEdge(g, src, dest);
    }
    else
    {
      cout << "Invalid edge. Please enter nodes between 0 and " << n - 1 << "." << endl;
      i--;
    }
  }

  print(g);
  int maxDepth;
  cout << "Enter the maximum depth: ";
  cin >> maxDepth;
  iterativeDFS(g, 0, maxDepth);

  return 0;
}
