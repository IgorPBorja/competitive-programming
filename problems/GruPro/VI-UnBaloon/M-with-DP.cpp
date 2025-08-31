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

const i64 INF = (i64)2e18;

// build dag and returns dist
pair<
    vector<vector<pair<i64, i64>>>,
    i64
> build_shortest_path_dag(
    const vector<vector<pair<i64, i64>>>& adj,
    i64 src,
    i64 target
) {
    const i64 n = adj.size();
    vector<vector<pair<i64, i64>>> sp(n);
    
    vector<i64> dist(n, INF);
    min_pq<pair<i64, i64>> pq;
    pq.emplace(0, src);
    while (!pq.empty()){
        auto[d, u] = pq.top();
        pq.pop();
        if (d >= dist[u]) continue;
        dist[u] = d;
        for (auto[w, v]: adj[u]){
            if (dist[u] + w < dist[v]){
                pq.emplace(dist[u] + w, v);
            }
        }
    }
    for (i64 u = 0; u < n; u++){
        for (auto[w, v]: adj[u]){
            if (dist[v] == dist[u] + w){
                // is on shortest path src->v
                sp[u].emplace_back(w, v);
            }
        }
    }
    return {sp, dist[target]};
}

// Shortest path is any path on the shortest path DAG SP
// Then on this DAG we can run DP to get the minimum max edge weight

// returns reverse toposort, which is the order in which
// by construction of the Shortest Paths DAG
// the first node on toposort will be sort
void toposort(
    i64 u,
    const vector<vector<pair<i64, i64>>>& sp_dag, 
    vector<i64>& vis,
    vector<i64>& order
){
    vis[u] = true;
    for (auto[_, v]: sp_dag[u]){
        if (!vis[v]) toposort(v, sp_dag, vis, order);
    }
    order.emplace_back(u);
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<vector<pair<i64, i64>>> adj(n);
    for (i64 i = 0; i < m; i++){
        i64 a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        adj[a].emplace_back(w, b);
    }

    auto[sp_dag, global_min_dist] = build_shortest_path_dag(adj, 0, n - 1);

    vector<i64> _vis(n, false), order;
    toposort(0, sp_dag, _vis, order);
    reverse(all(order));

    vector<i64> dp(n, INF);
    dp[0] = 0;
    for (i64 u: order){
        for (auto[w, v]: sp_dag[u]){
            dp[v] = min(dp[v], max(w, dp[u]));
        }
    }

    cout << global_min_dist << " " << dp[n - 1] << endl;
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
