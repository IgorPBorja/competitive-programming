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
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << setw(3) << (v != INF ? to_string(v) : "INF") << " "; \
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

namespace lca {
    const i64 N = (i64)1e5, LOGN = 20;
    i64 blift[LOGN + 1][N];
    vector<i64> level(N);
    vector<i64> parent(N);

    void dfs(i64 u, const vector<vector<i64>>& adj, i64 p = -1, i64 d = 0){
        level[u] = d;
        parent[u] = p;
        for (i64 v: adj[u]){
            if (v == p) continue;
            dfs(v, adj, u, d + 1);
        }
    }

    void init_lca(const vector<vector<i64>>& adj){
        const i64 n = adj.size();
        // set parent, level
        dfs(0, adj);
        // parent[root] := root to avoid breaking stuff
        parent[0] = 0;
        // printmsg("PARENT=", parent.begin(), parent.begin() + n);
        // printmsg("level=", level.begin(), level.begin() + n);

        for (i64 u = 0; u < n; u++){
            blift[0][u] = parent[u];
        }
        for (i64 k = 1; k <= LOGN; k++){
            for (i64 u = 0; u < n; u++){
                blift[k][u] = blift[k - 1][blift[k - 1][u]];
            }
        }
    }

    i64 jump(i64 u, i64 k){
        for (i64 i = 0; i <= LOGN; i++){
            if ((k >> i) & 1){
                u = blift[i][u];
            }
        }
        return u;
    }

    i64 lca(i64 u, i64 v){
        if (level[v] < level[u]) swap(u, v);
        v = jump(v, level[v] - level[u]);

        if (u == v) return u;

        for (i64 i = LOGN; i >= 0; i--){
            if (blift[i][u] != blift[i][v]){
                u = blift[i][u];
                v = blift[i][v];
            }
        }
        return parent[u];
    }
}

void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    lca::init_lca(adj);

    for (i64 i = 0; i < q; i++){
        i64 a[2], b[2];
        cin >> a[0] >> a[1] >> b[0] >> b[1];
        --a[0]; --a[1]; --b[0]; --b[1];
        
        i64 total = 0;
        i64 aa = lca::lca(a[0], a[1]);
        // cout << "AA: lca for a=" << a[0] + 1 << " b=" << a[1] + 1 << " is=" << aa + 1 << endl;
        i64 bb = lca::lca(b[0], b[1]);
        // cout << "BB: lca for a=" << b[0] + 1 << " b=" << b[1] + 1 << " is=" << bb + 1 << endl;

        i64 l_aa = lca::level[aa];
        i64 l_bb = lca::level[bb];
        bool seen_first_lca = false;
        for (i64 i = 0; i < 2; i++){
            for (i64 j = 0; j < 2; j++){
                i64 cross = lca::lca(a[i], b[j]);
                i64 lc = lca::level[cross];
                if (lc >= max(l_aa, l_bb)){
                    // both paths go through there
                    // use flag to avoid counting lowest lca many times
                    if (seen_first_lca){
                        total += lc - max(l_aa, l_bb);
                    } else {
                        total += lc - max(l_aa, l_bb) + 1;
                        seen_first_lca = true;
                    }
                }
            }
        }
        // for (i64 i = 0; i < 2; i++){
        //     i64 cross = lca::lca(a[i], bb);
        //     cout << "lca for a=" << a[i] + 1 << " BB=" << bb + 1 << " is=" << cross + 1 << endl;
        //     i64 lc = lca::level[cross];
        //     // a[i] goes to aa passing 
        //     if (lc >= l_aa){
        //         // a[i] goes to aa using common path, so does b[j]
        //         total += lc - l_aa + 1;
        //     }
        // }
        // for (i64 j = 0; j < 2; j++){
        //     i64 cross = lca::lca(aa, b[j]);
        //     // cout << "lca for a=" << a[i] + 1 << " b=" << b[j] + 1 << " is=" << cross + 1 << endl;
        //     cout << "lca for AA=" << aa + 1 << " b=" << b[j] + 1 << " is=" << cross + 1 << endl;
        //     i64 lc = lca::level[cross];
        //     if (lc >= l_bb){
        //         // a[i] goes to aa using common path, so does b[j]
        //         total += lc - l_bb + 1;
        //     }
        // }
        cout << total << endl;
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
