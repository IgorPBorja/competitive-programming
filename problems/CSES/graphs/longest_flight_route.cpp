#include <bits/stdc++.h>
using namespace std;

void DFS_label(vector<vector<int>>& adj, int s, bool vis[], 
                int& current,
                int f[]){
    vis[s] = true;
    for (int v: adj[s]){
        if (!vis[v]){
            DFS_label(adj, v, vis, current, f);
        }
    }
    f[s] = current;
    --current;
}

void topological_sort(vector<vector<int>>& adj, int f[]){
    int n = adj.size();
    int current = n - 1;
    bool vis[n] = {false};
    for (int u = 0; u < n; u++){
        if (!vis[u]){
            DFS_label(adj, u, vis, current, f);
        }
    }
}

vector<vector<int>> relabel_graph(vector<vector<int>>& adj, int f[]){
    /* 
    relabel i with f(i) to form a new graph f(G)
    then i -> j in f(G) ==> f^{-1}(i) -> f^{-1}(j) in G ==> i < j since f is topological order
    complexity: O(|V| + |E|)
    */
   vector<vector<int>> new_adj(adj.size());
   for (int i = 0; i < (int)adj.size(); i++){
    for (int j : adj[i]){
        new_adj[f[i]].emplace_back(f[j]);
    }
   }
   return new_adj;
}

int main(){
    int n, m, a, b;
    cin >> n >> m;
    vector<vector<int>> out_adj(n);
    int f[n]; // initial values do not matter, can be garbage
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        out_adj[a - 1].emplace_back(b - 1); // the -1 compensates 1-indexing
    }
    topological_sort(out_adj, f);
    out_adj = relabel_graph(out_adj, f);

    int dp[n] = {0}; // dp[i] = longest path to vertex f[n-1] (in new labeled graph) from f[i]
    int next_node[n]; // prev[i] = previous node in longest path from f[0] to i 
    for (int i = 0; i < n; i++) next_node[i] = -1; // placeholder for no path
    dp[f[n-1]] = 1;
    
    // in the new relabeled graph f(G), i -> j implies i < j
    // so we process from left to right
    for (int i = n-1; i >= 0; i--){
        if (i != f[n-1]){
            for (int j : out_adj[i]){
                // i -> j means j > i (==> already processed)
                if (dp[j] != 0 && dp[j] + 1 > dp[i]){
                    // dp[j] != 0 is necessary for the path to exist
                    // then the best path coming 
                    dp[i] = dp[j] + 1;
                    next_node[i] = j;
                }
            }
        }
    } 
    if (dp[f[0]] != 0)
    {
        // change of coordinates function (f-inverse)
        int inv_f[n];
        for (int i = 0; i < n; i++){
            inv_f[f[i]] = i;
        }
        // output
        cout << dp[f[0]] << '\n';
        int curr = f[0];
        while (curr != -1){
            cout << inv_f[curr] + 1 << ' '; // the +1 compensates 1-indexing
            curr = next_node[curr];
        }
    }
    else {
        cout << "IMPOSSIBLE";
    }
}