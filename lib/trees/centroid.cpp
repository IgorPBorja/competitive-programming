#include <bits/stdc++.h>
using namespace std;
 
namespace CentroidDecomposition {
    int subtree_size(int u, const vector<vector<int>>& adj, vector<int>& s, vector<int>& blocked, int p = -1){
        s[u] = 1;
        for (int v: adj[u]){
            if (v == p) continue;
            if (blocked[v]) continue;
            s[u] += subtree_size(v, adj, s, blocked, u);
        }
        return s[u];
    }

    // find centroid of subtree 
    int find_centroid(int u, const vector<vector<int>>& adj, vector<int>& s, vector<int>& blocked, int total_size, int p = -1){
        for (int v: adj[u]){
            if (v == p) continue;
            if (blocked[v]) continue;
            if (2 * s[v] >= total_size){
                return find_centroid(v, adj, s, blocked, total_size, u); // there can be only one such vertex
            }
        }
        return u;
    }

    // total_size = size of subtree rooted at root (considering deletions)
    // @return centroid subtree root
    int _build_centroid_tree(
        const vector<vector<int>>& adj,
        vector<int>& blocked,
        vector<vector<int>>& centroid_adj,
        vector<int>& sz,
        int total_size,
        int root = 0
    ){
        subtree_size(root, adj, sz, blocked);
        int c = find_centroid(root, adj, sz, blocked, total_size);
        blocked[c] = true;
        for (int v: adj[c]){
            if (blocked[v]) continue;
            // build centroid subtree on partition and get its root
            int c2 = _build_centroid_tree(adj, blocked, centroid_adj, sz, sz[v], v);
            centroid_adj[c].emplace_back(c2);
        }
        return c;
    }

    // @return pair (centroid tree root, directed centroid tree)
    pair<int, vector<vector<int>>> centroid_tree(const vector<vector<int>>& adj){
        const int n = adj.size();
        vector<int> blocked(n, false), sz(n);
        vector<vector<int>> centroid_adj(n);
        int master_centroid = _build_centroid_tree(
            adj, blocked, centroid_adj, sz, n
        );
        return {master_centroid, centroid_adj};
    }
}
