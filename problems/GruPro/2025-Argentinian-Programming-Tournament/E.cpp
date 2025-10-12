// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) debug << msg; for(auto it = v.begin(); it != v.end(); it++){debug << *it << " ";} debug << endl;
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

/*
At time t, a node u at depth d[u] contains

dp[t][u] = sum(a[v]) where:
* u ->* v with some amount of steps
* d[v] = d[u] + t

note: NOT monotonic

greedy:
    look at level L
    remove all nodes with value 0
    the sum is the answer for level L
    take LCA of those nodes: L - d[lca] is the time

we can take lca progressively: for level L with sz(L) nodes we have sz(L) * log n
LCA queries
==> sum sz(L) * log n = O(n log n)

HOWEVER lca can't be root, so we need to go per pair (child of root, level)

lca(x1, ..., xn) = lca(lca(x1, ..., x[n-1]), xn)
*/

constexpr i64 B = 30;
const i64 INF = (i64)2e18;

struct LCA {
    i64 n;
    vector<vector<i64>> adj;
    vector<i64> p, depth;
    vector<i64> blift[B];

    LCA(const vector<vector<i64>>& adj) : n(adj.size()), adj(adj), p(n), depth(n) {
        dfs(0);
        p[0] = 0;  // avoid problems with -1
        // cerr << "dfs ok" << endl;
        // print("parent array p=", p);
        calc();
    }

    void dfs(i64 u, i64 par = -1, i64 d = 0){  // 0 is root
        p[u] = par;
        depth[u] = d;
        for (i64 v: adj[u]){
            if (v == par) continue;
            dfs(v, u, d + 1);
        }
    }

    void calc(){
        blift[0] = p;
        for (i64 i = 1; i < B; i++){
            blift[i].resize(n);
            for (i64 j = 0; j < n; j++){
                blift[i][j] = blift[i - 1][blift[i - 1][j]];
            }
            // cerr << "processed i=" << i << endl;
        }
    }

    i64 up(i64 u, i64 k){
        for (i64 i = 0; i < B; i++){
            if (k & (1ll << i)) u = blift[i][u];
        }
        return u;
    }

    i64 lca(i64 u, i64 v){
        if (depth[v] < depth[u]) swap(u, v);
        v = up(v, depth[v] - depth[u]);
        if (u == v) return u;

        for (i64 i = B - 1; i >= 0; i--){
            if (blift[i][u] != blift[i][v]) {
                u = blift[i][u];
                v = blift[i][v];
            }
        }
        return p[u];
    }
};  // LCA OK!

void dfs(
    i64 u, i64 subroot,
    const vector<vector<i64>>& adj,
    vector<vector<pair<vector<i64>, i64>>>& per_level,
    vector<i64>& a, i64 p = 0, i64 d = 0  // parent starts at root
){
    // cerr << "at u=" << u << endl;
    if (a[u] > 0){
        per_level[subroot][d].first.emplace_back(u);
        per_level[subroot][d].second += a[u];
    }
    for (i64 v: adj[u]){
        if (v == p) continue;
        dfs(v, subroot, adj, per_level, a, u, d + 1);
    }
}

void dfs_height(
    i64 u, i64 subroot, const vector<vector<i64>>& adj,
    vector<i64>& h,
    i64 p = 0, i64 d = 1
){
    h[subroot] = max(h[subroot], d);
    for (i64 v: adj[u]){
        if (v != p){
            dfs_height(v, subroot, adj, h, u, d + 1);
        }
    }
}

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(n);
    vector<vector<i64>> adj(n);
    for (i64 i = 1; i < n; i++) cin >> a[i];
    vector<i64> subroots;
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        if (u == 0) subroots.emplace_back(v);
        else if (v == 0) subroots.emplace_back(u);
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    // cerr << "read ok" << endl;
    // print("subroots=", subroots);

    LCA lca(adj);
    // cerr << "lca setup ok" << endl;
    vector<vector<pair<vector<i64>, i64>>> per_level(n);
    vector<i64> h(n, 0);
    i64 ans = 0, min_turns = INF;
    for (i64 u: subroots){
        // cerr << "subroot u=" << u << endl;
        dfs_height(u, u, adj, h);
        // cerr << "h ok" << endl;
        per_level[u].assign(h[u], make_pair(vector<i64>(), 0));
        dfs(u, u, adj, per_level, a);
        // cerr << "per level build ok" << endl;
        for (i64 l = 0; l < h[u]; l++){
            if (per_level[u][l].second == 0) continue;  // empty level
            // cerr << "at relative level l=" << l << endl;
            // print("lvl=", per_level[u][l].first);
            i64 t = per_level[u][l].second;
            // cerr << "value t=" << t << endl;
            if (t >= ans){
                i64 common = per_level[u][l].first[0];
                for (i64 v: per_level[u][l].first){
                    common = lca.lca(common, v);
                }
                i64 rel_lca_level = lca.depth[common] - lca.depth[u];
                i64 turns = l - rel_lca_level + 1;
                if (t > ans || (t == ans && turns < min_turns)){
                    ans = t;
                    min_turns = turns;
                }
            }
        }
        // cerr << "processed subroot u=" << u << endl;
    }
    cout << ans << " " << min_turns << endl;
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
