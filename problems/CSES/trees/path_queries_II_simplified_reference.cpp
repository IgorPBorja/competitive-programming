#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << " ";} cerr << endl;

const i64 INF = 2e18;

namespace seg {
    i64 seg[(i64)8e5 + 10];
    i64 n;

    inline i64 merge(i64 a, i64 b) { return max(a, b); }

    void build(const vector<i64>& a, i64 l, i64 r, i64 node){  // O(n)
        if (l == r) seg[node] = a[l];
        else {
            i64 m = l + (r - l) / 2;
            build(a, l, m, 2 * node + 1);
            build(a, m + 1, r, 2 * node + 2);
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    void init(const vector<i64>& a){
        n = a.size();
        build(a, 0, n - 1, 0);
    }

    void _update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
        if (tl == p && p == tr) {
            seg[node] = x;
        } else {
            i64 tm = tl + (tr - tl) / 2;
            if (p <= tm) _update(p, x, tl, tm, 2 * node + 1);
            else _update(p, x, tm + 1, tr, 2 * node + 2);
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }
    void update_pt(i64 p, i64 x)  { _update(p, x, 0, n - 1, 0); }

    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr) return seg[node];
        else {
            if (r <= tm) return _query(l, r, tl, tm, 2 * node + 1);
            else if (l > tm) return _query(l, r, tm + 1, tr, 2 * node + 2);
            else return merge(
                _query(l, tm, tl, tm, 2 * node + 1),
                _query(tm + 1, r, tm + 1, tr, 2 * node + 2)
            );
        }
    }
    i64 query(i64 l, i64 r) { return _query(l, r, 0, n - 1, 0); }
}

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

    HLD(const vector<vector<i64>>& adj, const vector<i64>& a, i64 root = 0) :
        adj(adj), a(a), n(adj.size()), root(root) 
    {
        subtree(root);
        dfs(root);
        vector<i64> b(n);
        for (i64 i = 0; i < n; i++) b[pos[i]] = a[i];
        seg::init(b);
        // printmsg("a=", a.begin(), a.end());
        // printmsg("pos=", pos, pos + n);
        // printmsg("b=", b.begin(), b.end());
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

    // query from u to p^min(k, depth[u])(u), inclusive
    // NOTE: SUM QUERY HERE, other variations are possible
    i64 query_up(i64 u, i64 k){
        i64 s = -INF;
        while (u != -1 && k >= pos[u] - pos[head[u]] + 1){  // full path
            s = max(s, seg::query(pos[head[u]], pos[u]));
            k -= pos[u] - pos[head[u]] + 1;
            u = parent[head[u]];
        }
        if (u != -1){
            s = max(s, seg::query(pos[u] - k, pos[u]));
        }
        return s;
    }

    i64 lca(i64 u, i64 v){
        // cerr << "lca at u=" << u << " v=" << v << endl;
        if (pos[v] < pos[u]) swap(u, v);
        // now u is above or in another branch
        if (head[u] == head[v]) return u;
        else return lca(u, parent[head[v]]);
    }

    // query when values are on vertices
    i64 query_path_vertex(i64 u, i64 v){
        i64 l = lca(u, v);
        i64 left = query_up(u, depth[u] - depth[l]);
        i64 right = query_up(v, depth[v] - depth[l]);
        // cerr << "lca u=" << u << " v=" << v << " l=" << l << " left=" << left << " right=" << right << endl;
        return max(left, right);
    }

    void update_pt(i64 u, i64 x){  // set value to x
        seg::update_pt(pos[u], x);
        a[u] = x;
    }

    // void update_path(i64 u, i64 v){  // same stuff as lca
    //     if (pos[v] < pos[u]) swap(u, v);
    //     // now u is above or in another branch
    //     if (head[u] == head[v]) seg::update_range(pos[u], pos[v], x);
    //     else {
    //         seg::update_range(pos[head[v]], pos[v], x);
    //         update_path(u, parent[head[v]], x);
    //     }
    // }

    // subtree of v is entered at pos[v] and visited in contiguous range
    i64 query_subtree(i64 u){
        return seg::query(pos[u], pos[u] + sz[u] - 1);
    }
    // void update_subtree(i64 u, i64 x){
    //     seg::update_range(pos[u], pos[u] + sz[u] - 1, x);
    // }
};

int main(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> v(n);
    for (i64 i = 0; i < n; i++) cin >> v[i];
    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    HLD<(i64)2e5 + 10> hld(adj, v);
    for (i64 i = 0; i < q; i++){
        i64 mode, s, x, a, b;
        cin >> mode;
        if (mode == 1){
            cin >> s >> x;
            --s;
            hld.update_pt(s, x);
        } else {
            cin >> a >> b;
            --a; --b;
            cout << hld.query_path_vertex(a, b) << " ";
        }
    }
    cout << endl;
}
