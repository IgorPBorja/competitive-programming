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

// Shortest path is any DFS on the shortest path DAG SP
// So, binary search minimum M
// such that shortest path on graph with only
// edges on SP and of weigth <= M is still globally the shortest path

bool connects(
    i64 u,
    i64 target,
    i64 max_weight,
    const vector<vector<pair<i64, i64>>>& sp_dag,
    vector<i64>& vis
){
    vis[u] = true;
    if (u == target) return true;
    bool ok = false;
    for (auto[w, v]: sp_dag[u]){
        if (w <= max_weight && !vis[v]){
            ok |= connects(v, target, max_weight, sp_dag, vis);
        }
    }
    return ok;
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

    const i64 MAX_W = (i64)1e5;
    i64 l = 0, r = MAX_W, min_max_weight = MAX_W;

    while (l <= r){
        vector<i64> vis(n, false);
        const i64 mid = l + (r - l) / 2;
        if (connects(0, n - 1, mid, sp_dag, vis)){
            min_max_weight = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << global_min_dist << " " << min_max_weight << endl;
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
