#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define vi vector<int>
#define pii pair<int, int>

vi bfs(vvi& adj, int start, vector<bool>& vis){
  vi component;
  
  queue<int> q;
  q.emplace(start);
  component.emplace_back(start);
  vis[start] = true;
  while (!q.empty()){
    int u = q.front();
    q.pop();
    component.emplace_back(u);
    for (int v: adj[u]){
      if (!vis[v]){
        vis[v] = true;
        q.emplace(v);
      }
    }
  }
  return component;
}


int main(){
  int n, m;
  cin >> n >> m;
  vvi adj(n);
  
  int a, b;
  for (int i = 0; i < m; i++){
    cin >> a >> b;
    adj[a-1].emplace_back(b - 1); // the -1 corrects for 1-indexing
    adj[b-1].emplace_back(a - 1); // the -1 corrects for 1-indexing
  }
  vector<bool> vis(n, false);

  vvi comp_matrix;
  for (int i = 0; i < n; i++){
    if (!vis[i]){
      vi curr_comp = bfs(adj, i, vis); // O(n + m) total
      comp_matrix.emplace_back(curr_comp); // O(n) total 
    }
  }

  cout << comp_matrix.size() - 1 << '\n';
  for (int i = 0; i < comp_matrix.size() - 1; i++){
    cout << comp_matrix[i][0] + 1 << ' ' << comp_matrix[i + 1][0] + 1 << '\n';
    // the +1 corrects for 1-indexing
  }
}