// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
#define eb emplace_back
#define ep emplace
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

#define vi vector<i64>
#define vvi vector<vector<i64>> 

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 INF = (i64)2e18;

struct MaxSeg{
    vector<i64> seg, a;
    i64 n;

    MaxSeg() {}
    MaxSeg(const vector<i64>& __a) : a(__a), n(__a.size()) {
        seg.resize(4 * n);

        for (i64 i = 0; i < n; i++){
            this->update(i, a[i]);
        }
    }

    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr) return seg[node];
        else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm) return _query(l, r, tl, tm, 2 * node + 1);
            else if (l > tm) return _query(l, r, tm + 1, tr, 2 * node + 2);
            else return max(_query(l, tm, tl, tm, 2 * node + 1), _query(tm + 1, r, tm + 1, tr, 2 * node + 2));
        }
    }

    i64 query(i64 l, i64 r){
        return _query(l, r, 0, n - 1, 0);
    }

    void _update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
        const i64 tm = tl + (tr - tl) / 2;
        if (tl == tr && tr == p) {
            seg[node] = x;
        }
        else {
            if (p <= tm) _update(p, x, tl, tm, 2 * node + 1);
            else _update(p, x, tm + 1, tr, 2 * node + 2);
            seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    void update(i64 p, i64 x){
        _update(p, x, 0, n - 1, 0);
    }
};


struct HLD {
    // Segs are CONCATENATED into 1
    // each heavy path is visited sequentially, see dfs
    // so cur_pos ranges will reflect heavy paths
    i64 cur_pos = 0;

    vector<i64> abs_depth, pos, head_idx, heavy, parent;
    vector<vector<i64>> blift;
    MaxSeg seg;

    HLD(const vector<vector<i64>>& adj, const vector<i64>& node_values) {
        const i64 n = adj.size();
        i64 logn = 0;
        for (i64 tmp = n; tmp > 0; tmp >>= 1, ++logn) {}
        assert((1ll << logn) >= n);

        abs_depth.resize(n);
        pos.resize(n);
        head_idx.resize(n);
        heavy.assign(n, -1);
        parent.resize(n);
        blift.assign(logn + 1, vector<i64>(n));

        find_heavy_dfs(0, adj);
        dfs(0, adj, 0);
        do_lift();

        // reorder in heavy-path order
        vector<i64> v(n), inv_pos(n);
        for (i64 u = 0; u < n; u++){
            inv_pos[pos[u]] = u;
        }
        for (i64 i = 0; i < n; i++){
            // put value of element on position i (j: pos[j] = i ==> inv_pos[i])
            v[i] = node_values[inv_pos[i]];
        }
        seg = MaxSeg(v);
    }

    // return subtree size
    i64 find_heavy_dfs(i64 u, const vector<vector<i64>>& adj, i64 p = -1, i64 d = 0){
        parent[u] = p;
        abs_depth[u] = d;
        i64 total_sz = 1, max_children_sz = -1;
        for (i64 v: adj[u]){
            if (v == p) continue;
            i64 children_sz = find_heavy_dfs(v, adj, u, d + 1);
            total_sz += children_sz;
            if (children_sz > max_children_sz){
                max_children_sz = children_sz;
                heavy[u] = v;
            }
        }
        return total_sz;
    }

    void dfs(i64 u, const vector<vector<i64>>& adj, i64 cur_head){
        head_idx[u] = cur_head;
        pos[u] = cur_pos++;
        // visit heavy path first
        if (heavy[u] != -1) dfs(heavy[u], adj, cur_head);
        for (i64 v: adj[u]){
            if (v != parent[u] && v != heavy[u]){
                // light edge
                dfs(v, adj, v);
            }
        }
    }

    void do_lift(){
        copy(all(parent), blift[0].begin());
        for (i64 i = 1; i < (i64)blift.size(); i++){
            for (i64 u = 0; u < (i64)blift[i].size(); u++){
                if (blift[i - 1][u] != -1)
                    blift[i][u] = blift[i - 1][blift[i - 1][u]];
                else
                    blift[i][u] = -1;
            }
        }
    }

    i64 query_max_up(i64 u, i64 k){
        // cout << "running u=" << u << " k=" << k << endl;
        // cout << "head[" << u << "]=" << head_idx[u] << endl;
        i64 next = parent[head_idx[u]];
        // cout << "next=" << next << endl;
        // cout << "querying from l=" << max(pos[u] - k, (i64)0) << " to r=" << pos[u] << endl;
        // printmsg("seg=", segs[head_idx[u]].seg.begin(), segs[head_idx[u]].seg.end());
        i64 block = seg.query(max(pos[u] - k, pos[head_idx[u]]), pos[u]);
        i64 rel_pos = pos[u] - pos[head_idx[u]];
        // cout << "block=" << block << endl;
        if (k > rel_pos && next != -1){  // goes outside current heavy path
            return max(block, query_max_up(next, k - rel_pos - 1));
        } else {
            return block;
        }
    }

    i64 jump(i64 u, i64 k){
        for (i64 i = (i64)blift.size() - 1; i >= 0; i--){
            if (k & (1ll << i)) u = blift[i][u];
        }
        return u;
    }

    i64 lca(i64 u, i64 v){
        if (abs_depth[v] < abs_depth[u]) swap(u, v);
        v = jump(v, abs_depth[v] - abs_depth[u]);
        if (v == u) return u;

        for (i64 i = blift.size() - 1; i >= 0; i--){
            if (blift[i][u] != blift[i][v]){
                u = blift[i][u];
                v = blift[i][v];
            }
        }
        return parent[u];
    }

    i64 query_max_path(i64 u, i64 v){
        // find lca
        i64 l = lca(u, v);
        // cout << "lca=" << l << endl;
        // query up. Uses fact that max is idempotent
        return max(query_max_up(u, abs_depth[u] - abs_depth[l]), query_max_up(v, abs_depth[v] - abs_depth[l]));
    }

    void update(i64 u, i64 x){
        seg.update(pos[u], x);
    }
};


void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> v(n);
    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n; i++) cin >> v[i];
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    HLD hld(adj, v);

    for (i64 i = 0; i < q; i++){
        i64 mode, s, x, a, b;
        cin >> mode;
        if (mode == 1){
            cin >> s >> x;
            --s;
            hld.update(s, x);
        } else {
            cin >> a >> b;
            --a; --b;
            cout << hld.query_max_path(a, b) << " ";
        }
    }
    cout << endl;
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
