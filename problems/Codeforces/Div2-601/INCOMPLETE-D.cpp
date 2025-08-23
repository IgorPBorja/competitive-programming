// TODO STILL INCOMPLETE/WRONG
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

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 MOD = (i64)1e9 + 7;
const i64 INF = (i64)2e18;

struct Mint {
    i64 x;
    Mint() {}
    Mint(i64 _x) : x(_x % MOD) {}
    friend Mint operator+(Mint a, Mint b){
        return Mint((a.x + b.x) % MOD);
    }
    friend Mint operator-(Mint a){
        return Mint((MOD - a.x) % MOD);
    }
    friend Mint operator-(Mint a, Mint b){
        return Mint((a.x + MOD - b.x) % MOD);
    }
    friend Mint operator*(Mint a, Mint b){
        return Mint((a.x * b.x) % MOD);
    }
    Mint exp(i64 p){
        if (p == 0) return 1;
        else {
            Mint b = this->exp(p / 2);
            if (p % 2 == 0) return b * b;
            else return (*this) * b * b;
        }
    }
    Mint inv(){
        return this->exp(MOD - 2);
    }
    friend Mint operator/(Mint a, Mint b){
        return a * b.inv();
    }
    friend ostream& operator<<(ostream& os, Mint a){
        os << a.x;
        return os;
    }
};

struct MaxSegMOD {
    vector<Mint> seg;
    i64 n;

    MaxSegMOD(){}
    MaxSegMOD(i64 _n) : n(_n) {
        seg.assign(4 * n, 0);
    }

    Mint _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr) return seg[node];
        else {
            i64 tm = tl + (tr - tl) / 2;
            if (r <= tm) return _query(l, r, tl, tm, 2 * node + 1);
            else if (l > tm) return _query(l, r, tm + 1, tr, 2 * node + 2);
            else return _query(l, tm, tl, tm, 2 * node + 1) + _query(tm + 1, r, tm + 1, tr, 2 * node + 2);
        }
    }
    Mint query(i64 l, i64 r) { return _query(l, r, 0, n - 1, 0); }

    void _update_add(i64 p, Mint x, i64 tl, i64 tr, i64 node){
        i64 tm = tl + (tr - tl) / 2;
        if (tl == p && p == tr) seg[node] = seg[node] + x;
        else {
            if (p <= tm) _update_add(p, x, tl, tm, 2 * node + 1);
            else if (p > tm) _update_add(p, x, tm + 1, tr, 2 * node + 2);
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }
    void update_add(i64 p, Mint x) { _update_add(p, x, 0, n - 1, 0); }
};

// HLD implementation
// Tested on CSES Path Queries (https://cses.fi/problemset/task/1138)
// Query: sum of vertices from root to v
// Update: set value of v to x

// Implementation note: there is an implementation where
// you use a single seg-tree and the node positions are their
// time of visit in the DFS, where you **visit heavy edges first**
// (so heavy paths make contiguous ranges)
// However, this leads to a larger segtree and can be slower!

// uses some modifications: now the heavy edge is the edge with the largest subtree
// instead of the restriction s(c) >= s(v) / 2
// Still, going through light (i.e not heavy) edge reduces size by half
// Heavy path goes up to just the vertex before light edge
struct HLD {
    vector<i64> heavy;   // heavy[u] = v <==> uv is heavy edge
    vector<i64> sz;
    vector<i64> head;  // head[u] = start of heavy path that goes through u
    vector<i64> pos;   // depth of vertex in path. Head has depth 0
    vector<i64> parent;
    // NOTE: SegTree is the segment tree implementation
    // NOTE: SegTree needs default constructor
    vector<MaxSegMOD> segs;  
    vector<i64> a;
    vector<i64> depth;

    HLD(const vector<vector<i64>>& adj, i64 root = 0) {
        const i64 n = adj.size();
        heavy.resize(n);
        sz.resize(n);
        head.resize(n);
        pos.resize(n);
        parent.resize(n);
        segs.resize(n);
        depth.resize(n);

        subtree(root, adj);
        debug << "subtree OK" << endl;
        dfs(root, adj);
        debug << "hld partitioning OK" << endl;

        // build segment trees
        for (i64 h = 0; h < n; h++){
            if (h == head[h]){
                i64 cur = h;
                i64 path_size = 0;
                while (cur != -1){
                    ++path_size;
                    cur = heavy[cur];
                }
                segs[h] = MaxSegMOD(path_size);
            }
        }
        debug << "built segs OK" << endl;
    }

    void subtree(i64 u, const vector<vector<i64>>& adj, i64 p = -1, i64 d = 0){
        sz[u] = 1;
        depth[u] = d;
        for (i64 v: adj[u]){
            if (v == p) continue;
            subtree(v, adj, u, d + 1);
            sz[u] += sz[v];
        }
    }

    void dfs(i64 u, const vector<vector<i64>>& adj, i64 p = -1, i64 h = 0, i64 d = 0){
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
    Mint query_up(i64 u, i64 k){
        Mint s = 0;
        while (u != -1 && k >= pos[u]){
            s = s + segs[head[u]].query(0, pos[u]);
            u = parent[head[u]];
        }
        if (u != -1){  // k < pos[u]
            s = s + segs[head[u]].query(pos[u] - k, pos[u]);
        }
        debug << "query up from u=" << u << " to root equals s=" << s << endl;
        return s;
    }

    void update_add(i64 u, Mint x){  // set value to x
        segs[head[u]].update_add(pos[u], x);
    }
};


/*
Take an update (v, d).

Then probability of u in Subtree(v)\v being incremented is P(r not in Subtree(v) or r in Subtree(v) not in)
==> E[u] increments by (N-sz[v])/N * d
Else, if u not in Subtree(v) then probability of u being incremented is P(r in Subtree(v)) ==> E[u] is incremented by sz[u]/N * d
If u = v probability of u being incremented is 1 ==> E[v] is incremented by d

So, if we query u, u will have been updated by (N-sz[v_i])/N * d for each v_i between u and ROOT (since u will be in the subtree of v_i)
and by sz[v_i]/N * d for each v_i not satisfying this OR for v_i = u (to sum 1). So at time t

E_t[u] = sum(i=1..t, v_i between u and ROOT) (N-sz[v_i])/N * d_i + sum(i=1..t, v_i NOT between u and ROOT or u = v_i)sz[v_i]/N * d_i
= sum(i=1..t, v_i between u and ROOT) (N-sz[v_i])/N * d_i + sum(i=1..t, v_i NOT between u and ROOT)sz[v_i]/N * d_i + sum(i=1..t, u=v_i)sz[v_i]/N * d_i
= sum(i=1..t, v_i between u and ROOT) (N - 2 * sz[v_i])/N * d_i + sum(i=1..t)sz[v_i]/N * d_i + sum(i=1..t, u=v_i)sz[v_i]/N * d_i

The first sum only depends on v_i for each term and can be calculated using HLD
*/

void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    debug << "reading OK" << endl;
    HLD hld(adj);
    debug << "HLD OK" << endl;
    Mint total_acc = 0;
    vector<Mint> per_node_acc(n, 0);
    for (i64 i = 0; i < q; i++){
        i64 mode, v, d;
        cin >> mode >> v;
        --v;
        if (mode == 1){
            cin >> d;
            Mint delta = (Mint(n)-2 * hld.sz[v])/n * d;
            total_acc = total_acc + hld.sz[v] * d;
            per_node_acc[v] = per_node_acc[v] + hld.sz[v] * d;
            hld.update_add(v, delta);
        } else {
            debug << "total =" << total_acc << endl;
            debug << "per node total =" << per_node_acc[v] << endl;
            cout << hld.query_up(v, INF) + total_acc / n + per_node_acc[v] / n << endl;
        }
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
