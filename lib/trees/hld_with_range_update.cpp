// HLD implementation
// Tested on CSES Path Queries (https://cses.fi/problemset/task/1138)
//  and range update tested on problem L from ICPC Gran Premio de Mexico 2025 3ra fecha
// Query: sum of vertices from root to v
// Update: set value of v to x
// Call init_seg before using

// Implementation note: this is an implementation where
// you use a single seg-tree and the node positions are their
// time of visit in the DFS, where you **visit heavy edges first**
// (so heavy paths make contiguous ranges)
// However, this leads to a larger segtree and can be slower!
// An alternative is to use an array of segtrees (one for each path)

#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t

// heavy edge is the edge with the largest subtree
// going through light (i.e not heavy) edge reduces size by half
// heavy path goes up to just the vertex before light edge
template<size_t N> struct HLD {
    const vector<vector<i64>> adj;
    vector<i64> a;
    i64 parent[N], sz[N], depth[N],
        heavy[N],   // heavy[u] = v <==> uv is heavy edge
        head[N],  // head[u] = start of heavy path that goes through u
        pos[N];   // visit pos of vertex in dfs
    i64 global_pos = 0;
    i64 n, root;

    HLD(const vector<vector<i64>>& adj, i64 root = 0) :
        adj(adj), n(adj.size()), root(root) 
    {
        subtree(root);
        dfs(root);
    }

    void init_seg(const vector<i64>& vec) {
        a = vec;
        vector<i64> b(n);
        for (i64 i = 0; i < n; i++) b[pos[i]] = a[i];
        seg::init(b);
    }

    void subtree(i64 u, i64 p = -1, i64 d = 0){
        sz[u] = 1; depth[u] = d; parent[u] = p;
        for (i64 v: adj[u]){
            if (v == p) continue;
            subtree(v, u, d + 1);
            sz[u] += sz[v];
        }
    }

    void dfs(i64 u, i64 p = -1, i64 h = 0){
        i64 cur_sz = 0;
        pos[u] = global_pos++;
        head[u] = h;
        heavy[u] = -1;
        for (i64 v: adj[u]){
            if (v == p) continue;
            if (sz[v] > cur_sz){
                cur_sz = sz[v];
                heavy[u] = v;
            }
        }
        if (heavy[u] != -1) dfs(heavy[u], u, h);
        for (i64 v: adj[u]){
            if (v == p || v == heavy[u]) continue;
            dfs(v, u, v);
        }
    }

    // query from u to p^{k - 1}(u)
    // NOTE: sum query here, other variations are possible
    i64 query_up(i64 u, i64 k){
        i64 s = 0;
        while (u != -1 && k >= pos[u] - pos[head[u]] + 1){  // full path
            s += seg::query(pos[head[u]], pos[u]);
            k -= pos[u] - pos[head[u]] + 1;
            u = parent[head[u]];
        }
        if (u != -1 && k >= 1){
            s += seg::query(pos[u] - (k - 1), pos[u]);
        }
        return s;
    }

    i64 lca(i64 u, i64 v){
        if (pos[v] < pos[u]) swap(u, v);
        // now u is above or in another branch
        if (head[u] == head[v]) return u;
        else return lca(u, parent[head[v]]);
    }

    // query when values are on vertices
    i64 query_path_vertex(i64 u, i64 v){
        i64 l = lca(u, v);
        return (query_up(u, depth[u] - depth[l]) + query_up(v, depth[v] - depth[l]) + query_up(l, 1));
    }

    // query when a[i] = value for edge i->parent[i]
    i64 query_path_edge(i64 u, i64 v){
        i64 l = lca(u, v);
        return query_up(u, depth[u] - depth[l]) + query_up(v, depth[v] - depth[l]);
    }

    void update_pt(i64 u, i64 x){  // set value to x
        seg::update_pt(pos[u], x);
        a[u] = x;
    }

    void update_path_vertices(i64 u, i64 v, i64 x){  // same stuff as lca
        if (pos[v] < pos[u]) swap(u, v);
        // now u is above or in another branch
        if (head[u] == head[v]) seg::update_range(pos[u], pos[v], x);
        else {
            seg::update_range(pos[head[v]], pos[v], x);
            update_path_vertices(u, parent[head[v]], x);
        }
    }

    void update_path_edges(i64 u, i64 v, i64 x){  // same stuff as lca
        if (pos[v] < pos[u]) swap(u, v);
        // now u is above or in another branch
        if (head[u] == head[v]) {
            if (pos[u] < pos[v]) seg::update_range(pos[u] + 1, pos[v], x);
        }
        else {
            seg::update_range(pos[head[v]], pos[v], x);
            update_path_edges(u, parent[head[v]], x);
        }
    }

    // subtree of v is entered at pos[v] and visited in contiguous range
    i64 query_subtree(i64 u){
        return seg::query(pos[u], pos[u] + sz[u] - 1);
    }
    void update_subtree(i64 u, i64 x){
        seg::update_range(pos[u], pos[u] + sz[u] - 1, x);
    }
};
