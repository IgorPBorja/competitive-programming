#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define vi vector<int>
#define pii pair<int, int>

bool valid(int i, int j, int m, int n){
  return (i >= 0 && i < m && j >= 0 && j < n);
}

void bfs_ongrid(vvi& adj, pii start, vvi& visited,
              int m, int n){
  queue<pii> q;
  q.emplace(start);
  visited[start.first][start.second] = 1;
  while (!q.empty()){
    pii p = q.front();
    q.pop();
    int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
    for (int i = 0; i < 4; i++){
      if (valid(p.first + dy[i], p.second + dx[i], m, n)
        && adj[p.first + dy[i]][p.second + dx[i]] == 0
        && visited[p.first + dy[i]][p.second + dx[i]] == 0){
          visited[p.first + dy[i]][p.second + dx[i]] = 1;
          q.emplace(make_pair(p.first + dy[i], p.second + dx[i]));
        }
    }
  }
}

int main(){
  int m, n;
  cin >> m >> n;
  vvi grid(m, vi(n, 0));
  char c;
  for (int i = 0; i < m; i++){
    for (int j = 0; j < n; j++){
      cin >> c;
      grid[i][j] = (c == '.') ? 0 : 1;
    }
  }
  vvi vis(m, vi(n, 0));
  int cnt = 0;
  for (int i = 0; i < m; i++){
    for (int j = 0; j < n; j++){
      if (vis[i][j] == 0 && grid[i][j] == 0){
        ++cnt;
        bfs_ongrid(grid, make_pair(i, j), vis, m, n);
      }
    }
  }
  cout << cnt << '\n';
}