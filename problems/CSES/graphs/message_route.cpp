#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define vi vector<int>
/*
using bfs with dp? 

*/
const int INF = 2e9;

pair<vi, vi> bfs(vvi& adj, int end){
    /*dist[i] = distance from i to end*/
    /*prev[i] = next node in the shortest path from i to end with next_node[end] = -1
    and next_node[i] = -1 also if not end is not reachable from i*/
    vi dist((int)adj.size(), INF);
    vi next_node((int)adj.size(), -1);
    
    dist[end] = 1;
    std::queue<int> q;
    q.emplace(end);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int v : adj[u]){
            if (dist[v] == INF){
                dist[v] = 1 + dist[u];
                next_node[v] = u;
                q.emplace(v);
            }
        }
    }
    return make_pair(dist, next_node);
}

int main(){
    int n, m;
    cin >> n >> m;
    vvi adj(n);

    int a,b;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        // undirected graph
        adj[a - 1].emplace_back(b - 1);
        adj[b - 1].emplace_back(a - 1);
    }
    auto [dist, next_node] = bfs(adj, n - 1);
    if (dist[0] != INF){
        cout << dist[0] << '\n';
        // walk path
        int curr = 0;
        while (curr != -1){
            cout << curr + 1 << ' '; // +1 corrects 1-indexing
            curr = next_node[curr];
        }
    } else {
        cout << "IMPOSSIBLE";
    }
    
}
