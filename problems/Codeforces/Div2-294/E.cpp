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
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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
    vector<vector<i64>> lift;
    vector<i64> p;
    vector<i64> sz, h;
    i64 n, ilog;

    LCA(const vector<vector<i64>> &adj) : n(adj.size()) {
        sz.resize(n);
        p.assign(n, -1);
        h.resize(n);
        ilog = 0;
        while ((1ll << (ilog + 1)) <= n) ++ilog;
        lift.assign(ilog + 1, vector<i64>(n, -1));

        dfs_sz(adj, 0);
        do_lift();
    }

    i64 query(i64 x, i64 y){
        // get LCA
        if (x == y) return n;

        if (h[x] > h[y]) swap(x, y);
        i64 x0 = x, y0 = y;
        i64 lca;

        y = jump(y, h[y] - h[x]);
        if (x == y){
            lca = x;
        } else {
            for (i64 i = ilog; i >= 0; i--){
                if (lift[i][x] != lift[i][y]){
                    x = lift[i][x];
                    y = lift[i][y];
                }
            }
            lca = p[x];
        }

        // equidistant is LCA
        // can go down OR go up
        if (h[x0] == h[y0]){
            // on LCA path from y: we have sz[y]
            // on LCA path from x: we have sz[x]
            // UP: n - sz[lca], DOWN: sz[lca] - (sz[x] + sz[y])
            return (n - sz[lca]) + (sz[lca] - (sz[x] + sz[y]));
        }
        // since h[y0] > h[x0]: try to jump the average of h[x0] - h[lca] and h[y0] - h[lca] from y
        else if ((h[y0] + h[x0]) % 2 == 1){
            return 0;
        }
        else {
            i64 delta = (h[x0] - h[lca] + h[y0] - h[lca]) / 2;
            i64 r = jump(y0, delta);
            if (delta > 0){
                i64 r1 = jump(y0, delta - 1);
                return sz[r] - sz[r1];
            } else {
                return sz[r];
            }
        }
    }

    void do_lift(){
        for (i64 j = 0; j < n; j++){
            lift[0][j] = p[j];
        }
        for (i64 i = 1; i <= ilog; i++){
            for (i64 j = 0; j < n; j++){
                if (lift[i - 1][j] != -1){
                    lift[i][j] = lift[i - 1][lift[i - 1][j]];
                }
            }
        }
    }

    i64 jump(i64 u, i64 k){
        for (i64 i = ilog; i >= 0 && u != -1; i--){
            if ((k >> i) & 1) {
                u = lift[i][u];
            }
        }
        return u;
    }

    void dfs_sz(const vector<vector<i64>> &adj, i64 u, i64 parent = -1, i64 height = 0){
        p[u] = parent;
        h[u] = height;
        sz[u] = 1;
        for (i64 v: adj[u]){
            if (v == parent) continue;
            dfs_sz(adj, v, u, height + 1);
            sz[u] += sz[v];
        }
    }

};

void solve(){
    i64 n;
    i64 a, b;
    cin >> n;

    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n - 1; i++){
        cin >> a >> b;
        --a; --b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }

    LCA lca(adj);

    i64 m;
    cin >> m;
    for (i64 i = 0; i < m; i++){
        cin >> a >> b;
        --a; --b;
        cout << lca.query(a, b) << endl;
    }
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
