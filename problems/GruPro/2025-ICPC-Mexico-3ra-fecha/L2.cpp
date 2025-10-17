#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << " ";} cerr << endl;

const i64 MOD = (i64)1e9 + 7;

namespace seg { // lazy seg
    constexpr i64 N = 2e5 + 10;
    // lazy[node] is something not propagated to child nodes
    // (but already propagated to current node)
    // otherwise queries are messed up
    i64 seg[4 * N], lazy[4 * N];
    i64 n;

    inline i64 merge(i64 a, i64 b){
        return (a + b) % MOD;
    }

    void build(const vector<i64>& a, i64 l, i64 r, i64 node){
        if (l == r) seg[node] = a[l];
        else {
            const i64 m = l + (r - l) / 2;
            build(a, l, m, 2 * node + 1);
            build(a, m + 1, r, 2 * node + 2);
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    void init(const vector<i64>& a){
        n = a.size();
        fill(lazy, lazy + 4 * n, 1);  // lazy is multiplicative here  // lazy is multiplicative here
        build(a, 0, n - 1, 0);
        // print_lazy();
    }


    void prop(i64 node){
        seg[2 * node + 1] = (seg[2 * node + 1] * lazy[node]) % MOD;
        seg[2 * node + 2] = (seg[2 * node + 2] * lazy[node]) % MOD;
        lazy[2 * node + 1] = (lazy[2 * node + 1] * lazy[node]) % MOD;
        lazy[2 * node + 2] = (lazy[2 * node + 2] * lazy[node]) % MOD;
        lazy[node] = 1;
    }

    // multiply everyone by x
    void _update_range(i64 l, i64 r, i64 x, i64 tl, i64 tr, i64 node){
        prop(node);  // now there are no pending props
        if (l == tl && r == tr){
            seg[node] = (seg[node] * x) % MOD;
            lazy[node] = (lazy[node] * x) % MOD;
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm) _update_range(l, r, x, tl, tm, 2 * node + 1);
            else if (l > tm) _update_range(l, r, x, tm + 1, tr, 2 * node + 2);
            else {
                _update_range(l, tm, x, tl, tm, 2 * node + 1);
                _update_range(tm + 1, r, x, tm + 1, tr, 2 * node + 2);
            }
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }
    void update_range(i64 l, i64 r, i64 x) { _update_range(l, r, x, 0, n - 1, 0); }

    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        prop(node);  // now there are no pending props
        if (l == tl && r == tr){
            return seg[node];
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm) return _query(l, r, tl, tm, 2 * node + 1);
            else if (l > tm) return _query(l, r, tm + 1, tr, 2 * node + 2);
            else {
                return merge(
                    _query(l, tm, tl, tm, 2 * node + 1),
                    _query(tm + 1, r, tm + 1, tr, 2 * node + 2)
                );
            }
        }
    }
    i64 query(i64 l, i64 r) { return _query(l, r, 0, n - 1, 0);}
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
            s = (s + seg::query(pos[head[u]], pos[u])) % MOD;
            k -= pos[u] - pos[head[u]] + 1;
            u = parent[head[u]];
        }
        if (u != -1 && k >= 1){
            s = (s + seg::query(pos[u] - (k - 1), pos[u])) % MOD;
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
        return (query_up(u, depth[u] - depth[l]) + query_up(v, depth[v] - depth[l]) + query_up(l, 1)) % MOD;
    }

    // query when a[i] = value for edge i->parent[i]
    i64 query_path_edge(i64 u, i64 v){
        i64 l = lca(u, v);
        i64 left = query_up(u, depth[u] - depth[l]),
            right = query_up(v, depth[v] - depth[l]);
        // cerr << "u=" << u << " v=" << v << " left=" << left << " right=" << right << endl;
        return (left + right) % MOD;
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

void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<vector<i64>> g(n);
    vector<vector<pair<i64, i64>>> wg(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
        wg[u].emplace_back(v, w);
        wg[v].emplace_back(u, w);
    }

    HLD<(i64)2e5 + 100> hld(g);
    vector<i64> a(n);
    for (i64 u = 0; u < n; u++) {
        for (auto[v, w]: wg[u]){
            if (v == hld.parent[u]){
                a[u] = w;
            }
        }
    }
    hld.init_seg(a);

    for (i64 i = 0; i < q; i++){
        i64 u, v, x;
        cin >> u >> v >> x;
        --u; --v;
        hld.update_path_edges(u, v, x);
        cout << hld.query_path_edge(u, v) << endl;
    }
}
 
signed main(){
	fastio;
	int t;
#ifdef TESTCASES
	cin >> t;
#else
	t = 1;
#endif
	while (t--){
		solve();
	}
}
