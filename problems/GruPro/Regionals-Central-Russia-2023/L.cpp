#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

const i64 INF = (i64)2e18;

signed main(){
    i64 n, m;
    cin >> n >> m;

    i64 a[n][m];
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            char c;
            cin >> c;
            a[i][j] = (c == '.');  // not painted = .
        }
    }

    vector<vector<pair<i64, i64>>> adj(n * m + 2);
    // top (directed)
    for (i64 i = 0; i < m; i++){
        adj[n * m].emplace_back(i, a[0][i]);
    }
    // bottom (directed), cost is always 0
    for (i64 i = 0; i < m; i++){
        adj[(n - 1) * m + i].emplace_back(n * m + 1, 0);
    }
    for (i64 i = 0; i + 1 < n; i++){
        for (i64 j = 0; j < m; j++){
            if (i % 2 == 0){
                // (i,j) -> (i+1,j-1), (i+1,j)
                adj[m * i + j].emplace_back(m * (i + 1) + j, a[i + 1][j]);
                adj[m * (i + 1) + j].emplace_back(m * i + j, a[i][j]);

                if (j - 1 >= 0){
                    adj[m * i + j].emplace_back(m * (i + 1) + j - 1, a[i + 1][j - 1]);
                    adj[m * (i + 1) + j - 1].emplace_back(m * i + j, a[i][j]);
                }
            } else {
                // (i,j) -> (i+1,j),(i+1,j+1)
                adj[m * i + j].emplace_back(m * (i + 1) + j, a[i + 1][j]);
                adj[m * (i + 1) + j].emplace_back(m * i + j, a[i][j]);
                
                if (j + 1 < m){
                    adj[m * i + j].emplace_back(m * (i + 1) + j + 1, a[i + 1][j + 1]);
                    adj[m * (i + 1) + j + 1].emplace_back(m * i + j, a[i][j]);
                }
            }
            if (j + 1 < m){ // right
                adj[m * i + j].emplace_back(m * i + j + 1, a[i][j + 1]);
                adj[m * i + j + 1].emplace_back(m * i + j, a[i][j]);
            }
        }
    }

    // bfs-01
    vector<i64> dist(n * m + 2, +INF);
    deque<tuple<i64, i64, i64>> d;
    d.emplace_front(n * m, 0, 0);
    while (!d.empty()){
        auto[u, cur, delta] = d.front();
        d.pop_front();
        if (dist[u] != +INF){
            // already visited
            continue;
        }
        // cout << "visiting u=" << u << " cur=" << cur << " delta=" << delta << endl;
        dist[u] = cur + delta;
        for (auto[v, delta2]: adj[u]){
            if (delta2 == 0){
                d.emplace_front(v, dist[u], 0);
            } else {
                d.emplace_back(v, dist[u], 1);
            }
        }
    }
    cout << dist[n * m + 1] << endl;
}