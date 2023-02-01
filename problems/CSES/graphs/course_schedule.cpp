#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define vi vector<int>

void DFS(const vvi& adj, int s, bool vis[], int& curr, int f[]){
    vis[s] = true;
    for (int v: adj[s]){
        if (!vis[v]){
            DFS(adj, v, vis, curr, f);
        }
    }
    f[s] = curr;
    --curr;
}

void topological_sort(const vvi& adj, int f[]){
    bool vis[(int)adj.size()] = {false};
    int curr = (int)adj.size() - 1;
    for (int i = 0; i < (int)adj.size(); i++){
        if (!vis[i]){
            DFS(adj, i, vis, curr, f);
        }
    }
}

bool check_topo(vvi& adj, int f[]){
    for (int u = 0; u < (int)adj.size(); u++){
        for (int v : adj[u]){
            if (f[u] >= f[v]){
                return false;
            }
        }
    }
    return true;
}

int main(){
    int n, m, a, b;
    cin >> n >> m;
    vvi adj(n);
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a-1].emplace_back(b-1);
    }
    int f[n], inv_f[n];
    // O(|V| + |E|)
    topological_sort(adj, f);

    if (check_topo(adj, f)){ // O(|V| + |E|) also
        for (int i = 0; i < n; i++){
            inv_f[f[i]] = i;
        }
        for (int i = 0; i < n; i++){
            cout << inv_f[i] + 1 << ' ';
        }
    } else {
        cout << "IMPOSSIBLE";
    }
}