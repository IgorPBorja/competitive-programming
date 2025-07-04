#define testcases
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define printmsg(msg, first, last) \
    cout << msg; \
    for (auto it = first; it != last; it++) { \
        cout << *it << " "; \
    } \
    cout << endl

const i64 INF = (i64)2e18;

template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> p){
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

struct DSU {
	vector<i64> p, sz, min_edge_component;

	DSU(i64 n){
		p.resize(n);
		iota(p.begin(), p.end(), 0);
		sz.assign(n, 1);
		min_edge_component.assign(n, INF);
	}

	i64 find(i64 x){
		return (x == p[x] ? x : p[x] = find(p[x]));
	}

	bool unite(i64 x, i64 y, i64 w){
		x = find(x);
		y = find(y);
		if (x == y) return false;
		if (sz[x] > sz[y]) swap(x, y);

		i64 m = min(min_edge_component[x], min_edge_component[y]);
		min_edge_component[x] = min(m, w);
		min_edge_component[y] = min(m, w);

		// join x->y
		p[x] = y;
		sz[y] += sz[x];

		return true;
	}
};

void solve(){
	i64 n, m;
	cin >> n >> m;
	
	// vector<vector<pair<i64, i64>>> adj(n);
	// for (i64 i = 0; i < m; i++){
	// 	i64 u, v, w;
	// 	cin >> u >> v >> w;
	// 	--u; --v;
	// 	adj[u].emplace_back(w, v);
	// 	adj[v].emplace_back(w, u);
	// }
	// for (i64 u = 0; u < n; u++) sort(adj[u].begin(), adj[u].end());
	vector<tuple<i64, i64, i64>> edges(m);
	for (i64 i = 0; i < m; i++){
		cin >> get<1>(edges[i]) >> get<2>(edges[i]) >> get<0>(edges[i]);
		--get<1>(edges[i]);
		--get<2>(edges[i]);
	}

	DSU d(n);
	sort(edges.begin(), edges.end());
	// best path: every time a bridge connects 0 to n-1 OR (0,n-1) is connected to something
	// then update max edge and use the min edge of the component
	// It might be the case an update is good even after (0,n-1) are connected
	// e.x: 
	/*
	6 5
	4 5 17
    1 6 15
    1 3 17
    2 5 13
    3 4 10
    */
	i64 max_edge = -INF;
	i64 ans = INF;
	for (i64 i = 0; i < m; i++){
		auto[w, u, v] = edges[i];
		bool is_bridge = d.unite(u, v, w);
		if (is_bridge && d.find(n-1) == d.find(0)){
    		max_edge = max(max_edge, w);
    		ans = min(ans, max_edge + d.min_edge_component[d.find(0)]);
		}
	}
	cout << ans << endl;
}

signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}
