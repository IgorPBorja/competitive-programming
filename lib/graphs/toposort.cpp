#include <bits/stdc++.h>
using namespace std;

namespace Graph {
    int c;

    void dfs(
		int u, vector<vector<int>> &G, vector<bool> &vis, vector<int> &order
	){
        vis[u] = true;
        for (int v: G[u]){
            if (!vis[v]){
                dfs(v, G, vis, order);
            }
        }
        order[u] = c;
        --c;
    }

    vector<int> toposort(vector<vector<int>> &G){
        c = G.size() - 1;
        const int n = G.size();
        vector<bool> vis(n, false);
        vector<int> order(n);
        for (int u = 0; u < n; u++){
            if (!vis[u]){
                dfs(u, G, vis, order);
            }
        }
        // validate order
        for (int u = 0; u < n; u++){
            for (int v: G[u]){
                if (order[u] >= order[v]) {
                    return vector<int>();
                }
            }
        }
        return order;
    }
}