#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t

namespace lca {
	const i64 N = 2e5 + 100, LOGN = 20;
	i64 parent[N], level[N];
	i64 blift[LOGN + 1][N];

	void dfs(i64 u, const vector<vector<i64>>& adj, i64 p = -1, i64 d = 0){
		parent[u] = p;
		level[u] = d;
		for (i64 v: adj[u]){
			if (v == p) continue;
			dfs(v, adj, u, d + 1);
		}
	}
	void init(const vector<vector<i64>>& adj, i64 root = 0){
		const i64 n = adj.size();
		dfs(root, adj);
		parent[root] = root;  // fix root
		for (i64 u = 0; u < n; u++) blift[0][u] = parent[u];
		for (i64 k = 1; k <= LOGN; k++){
			for (i64 u = 0; u < n; u++){
				blift[k][u] = blift[k - 1][blift[k - 1][u]];
			}
		}
	}
	i64 up(i64 u, i64 k){
		for (i64 i = 0; i <= LOGN; i++){
			if (k & (1ll << i)){
				u = blift[i][u];
			}
		}
		return u;
	}
	i64 lca(i64 u, i64 v){
		if (level[v] < level[u]) swap(u, v);
		v = up(v, level[v] - level[u]);
		if (u == v) return u;
		// loop invariant: u and v are distinct
		// (have not reached a common ancestor yet)
		for (i64 i = LOGN; i >= 0; i--){
			if (blift[i][u] != blift[i][v]){
				// keeps loop invariant -> greedily take it!
				u = blift[i][u];
				v = blift[i][v];
			}
		}
		// at the end of the invariant we must be just one level below the LCA
		// otherwise we could have jumped more
		return parent[u];
	}
}



void solve(){
    i64 n, q;
    cin >> n >> q;

    vector<vector<i64>> tree(n);
    for (i64 i = 1; i < n; i++){  // root is 0
        i64 p;
        cin >> p;
        --p;
        tree[p].emplace_back(i);
        tree[i].emplace_back(p);
    }

    lca::init(tree, 0);  // using some 
    i64 a, b;
    for (i64 i = 0; i < q; i++){
        cin >> a >> b;
        --a; --b;
        cout << lca::lca(a, b) + 1 << endl;
    }
}
 
signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--){
		solve();
	}
}
