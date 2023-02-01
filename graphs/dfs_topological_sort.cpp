#include <bits/stdc++.h>
using namespace std;

void topological_sort(vector<vector<int>>& adj,
                      int n,
                      int res[])
{
  // res is a permutation of 0 -> n - 1
  // so res[i] = j ==> f(j) = i
  // i.e res[i] = f^{-1}(i) (the pre-image)

  // first, we count the indegree of each vertice in O(V + E)
  int deg[n] = {0};
  for (int u = 0; u < n; u++){
    for (int v: adj[u]){
      ++deg[v];
    }
  }
  // then, we do dfs only from the unvisited nodes with indegrees 0
  // since there are no cycles (the graph is a DAG), each connected component has at least
  // one vertice with indegree 0
  bool vis[n] = {false};
  int curr = 1;
  for (int u = 0; u < n; u++){
    if (deg[u] == 0 && !vis[u]){
      vis[u] = true;
      stack<int> s;
      s.push(u);
      while (!s.empty()){
        int v = s.top(); 
        s.pop(); 
        vis[v] = true;
        // calculate f(v)
        res[v] = curr; 
        ++curr;
        // loop through adjacencies
        for (int w: adj[v]){
          if (!vis[w])
            s.push(w);
        }
      }
    }
  }
}

int main(){
  // assumes graph in the following format
  /*
  n, m
  a1, b1
  ...
  a_m, b_m

  where each (a_i, b_i) is an edge and 1 <= a_i, b_i <= n
  */
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  int res[n]; // initial values don't matter, can be garbage
  for (int i = 0; i < m; i++){
    int a, b;
    cin >> a >> b;
    adj[a - 1].emplace_back(b - 1); // adjust for 1-indexing
  }

  topological_sort(adj, n, res);

  for (int i = 0; i < n; i++){
    cout << "f(" << i + 1 << ") = " << res[i] << "\t";
  }
}