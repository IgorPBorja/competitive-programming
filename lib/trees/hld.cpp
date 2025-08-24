// HLD implementation
// Tested on CSES Path Queries (https://cses.fi/problemset/task/1138)
// Query: sum of vertices from root to v
// Update: set value of v to x

// Implementation note: there is an implementation where
// you use a single seg-tree and the node positions are their
// time of visit in the DFS, where you **visit heavy edges first**
// (so heavy paths make contiguous ranges)
// However, this leads to a larger segtree and can be slower!

#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t

// uses some modifications: now the heavy edge is the edge with the largest subtree
// instead of the restriction s(c) >= s(v) / 2
// Still, going through light (i.e not heavy) edge reduces size by half
// Heavy path goes up to just the vertex before light edge
using tree = vector<vector<i64>>;
struct HLD {
    vector<i64> heavy;   // heavy[u] = v <==> uv is heavy edge
    vector<i64> sz;
    vector<i64> head;  // head[u] = start of heavy path that goes through u
    vector<i64> pos;   // depth of vertex in path. Head has depth 0
    vector<i64> parent;
    // NOTE: SegTree is the segment tree implementation
    // NOTE: SegTree needs default constructor
    vector<SegTree> segs;  
    vector<i64> a;
    vector<i64> depth;

    HLD(const tree& adj, const vector<i64>& _a, i64 root = 0) : a(a) {
        const i64 n = adj.size();
        heavy.resize(n);
        sz.resize(n);
        head.resize(n);
        pos.resize(n);
        parent.resize(n);
        segs.resize(n);

        subtree(root, adj);
        dfs(root, adj);

        // build segment trees
        for (i64 h = 0; h < n; h++){
            if (h == head[h]){
                vector<i64> path;
                i64 cur = h;
                while (cur != -1 && head[cur] == h){
                    path.emplace_back(a[cur]);  // add value
                    cur = heavy[cur];
                }
                segs[h] = SegTree(path);
            }
        }
    }

    void subtree(i64 u, const tree& adj, i64 p = -1, i64 d = 0){
        sz[u] = 1;
        depth[u] = d;
        for (i64 v: adj[u]){
            if (v == p) continue;
            subtree(v, adj, u, d + 1);
            sz[u] += sz[v];
        }
    }

    void dfs(i64 u, const tree& adj, i64 p = -1, i64 h = 0, i64 d = 0){
        i64 cur_sz = 0;
        pos[u] = d;
        head[u] = h;
        parent[u] = p;
        heavy[u] = -1;
        for (i64 v: adj[u]){
            if (v == p) continue;
            if (sz[v] > cur_sz){
                cur_sz = sz[v];
                heavy[u] = v;
            }
        }
        for (i64 v: adj[u]){
            if (v == p) continue;
            if (v == heavy[u]){
                dfs(v, adj, u, h, d + 1);
            } else {
                dfs(v, adj, u, v, 0);
            }
        }
    }

    // query from u to p^min(k, depth[u])(u), inclusive
    // NOTE: SUM QUERY HERE, other variations are possible
    i64 query_up(i64 u, i64 k){
        i64 s = 0;
        while (u != -1 && k >= pos[u]){
            s += segs[head[u]].query(0, pos[u]);
            u = parent[head[u]];
        }
        if (u != -1){  // k < pos[u]
            s += segs[head[u]].query(pos[u] - k, pos[u]);
        }
        return s;
    }

    i64 query_path(i64 u, i64 v){
        // TODO implement LCA!
        i64 l = lca(u, v);
        return query_up(u, depth[u] - depth[l]) + query_up(v, depth[v] - depth[l]) - a[l];
    }

    void update(i64 u, i64 x){  // set value to x
        segs[head[u]].update(pos[u], x);
    }
};
