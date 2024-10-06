// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

struct LCA {
    LCA(const vector<vector<i64>> &adj, const i64 root = 0){
        p.resize(adj.size());
        h.resize(adj.size());
        acc.assign(adj.size(), 0);
        dfs(root, adj);
        build();
    }

    i64 lca(i64 u, i64 v){
        if (h[u] > h[v]) swap(u, v);

        v = up(v, h[v] - h[u]);
        if (u == v) return u;

        const i64 ilog = blift.size() - 1;
        for (i64 i = ilog; i >= 0; i--){
            if (blift[i][u] != blift[i][v]){
                u = blift[i][u];
                v = blift[i][v];
            }
        }
        return p[u];
    }

    void visit_path(i64 u, i64 v){
        i64 l = lca(u, v);
        if (l != u){  // has to go up 
            ++acc[u];
            --acc[l];
        }
        if (l != v){  // has to go up
            ++acc[v];
            --acc[l];
        }
    }

    vector<i64> prefix_tree(const i64 root = 0){
        // rebuild adj
        const i64 n = p.size();
        vector<vector<i64>> adj(n);
        for (i64 u = 0; u < n; u++){
            if (p[u] != -1){
                adj[p[u]].emplace_back(u);
            }
        }
        dfs_prefix(root, adj);
        return acc;
    }

    i64 parent(i64 u){
        return p[u];
    }

    i64 up(i64 u, i64 k){
        for (i64 i = 0; i < blift.size() && u != -1; i++){
            if ((k >> i) & 1){
                u = blift[i][u];
            }
        }
        return u;
    }

private:
    vector<i64> p, h;
    vector<vector<i64>> blift;
    vector<i64> acc;

    void dfs(i64 u, const vector<vector<i64>> &adj, i64 depth = 0, i64 parent = -1){
        p[u] = parent;
        h[u] = depth;
        for (i64 v: adj[u]){
            if (v == parent) continue;
            dfs(v, adj, depth + 1, u);
        }
    }

    void dfs_prefix(i64 u, const vector<vector<i64>> &adj, i64 p = -1){
        for (i64 v: adj[u]){
            if (v == p) continue;
            dfs_prefix(v, adj, u);
            acc[u] += acc[v];
        }
    }

    void build(){
        const i64 n = p.size();
        i64 ilog = 0;
        while ((1ll << (ilog + 1)) <= n){
            ++ilog;
        }
        blift.assign(ilog + 1, vector<i64>(n, -1));
        for (i64 u = 0; u < n; u++){
            blift[0][u] = p[u];
        }
        for (i64 i = 1; i <= ilog; i++){
            for (i64 u = 0; u < n; u++){
                if (blift[i - 1][u] != -1){
                    blift[i][u] = blift[i - 1][blift[i - 1][u]];
                }
            }
        }
    }
};

void solve(){
    i64 n;
    cin >> n;

    vector<vector<i64>> adj(n);
    vector<pair<i64, i64>> edges;
    for (i64 i = 0; i < n - 1; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
        edges.emplace_back(a, b);
    }

    LCA lca(adj);

    i64 k;
    cin >> k;
    for (i64 i = 0; i < k; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        lca.visit_path(a, b);
    }

    vector<i64> ans = lca.prefix_tree();

    for (auto[a, b]: edges){
        if (a == lca.parent(b)){
            cout << ans[b] << " ";
        } else {
            cout << ans[a] << " ";
        }
    }
    cout << endl;
}
 
signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
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
