#include <bits/stdc++.h>
using namespace std;

const int INF = (int)2e9;

namespace Tarjan {
    vector<int> lowlink, t_in;
    vector<pair<int, int>> dfs_tree_edges;
    int timer;

    void dfs(int u, const vector<vector<int>> &g, vector<bool> &vis,
			int parent = -1){
        vis[u] = true;
        t_in[u] = lowlink[u] = timer++;
        for (int to: g[u]){
            if (to == parent) continue;
            else if (vis[to]){
                // back edge on DFS tree
                lowlink[u] = min(t_in[to], lowlink[u]);
            } else {
                dfs(to, g, vis, u);
                dfs_tree_edges.emplace_back(u, to);
                lowlink[u] = min(lowlink[to], lowlink[u]);
            }
        }
    }

    // lowlink(u) = min(t_in(u), min_{p->u}t_in(u), min_{u->to em tree}lowlink(to))
    vector<vector<pair<int, int>>> dfs_tree_bridges(const vector<vector<int>> &g) {
        const int n = g.size();
        vector<bool> vis(n, false);
        lowlink = vector<int>(n, INF);
        t_in = vector<int>(n, INF);
        dfs_tree_edges.clear();
        timer = 0;

        for (int u = 0; u < n; u++){
            if (!vis[u]){
                dfs(u, g, vis);
            }
        }

        vector<vector<pair<int, int>>> h(n);
        for (auto[v, to]: dfs_tree_edges){
            if (lowlink[to] > t_in[v]){
                h[v].emplace_back(to, 1);
            } else {
                h[v].emplace_back(to, 0);
            }
        }
        return h;
    }
}