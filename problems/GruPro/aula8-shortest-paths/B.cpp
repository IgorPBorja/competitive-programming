#define TESTCASES
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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
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
const i64 INF = 1e18;

// is O(|V|^2 log V) since graph is dense
// since |V| = 2^n complexity stays at n * 4^n = 10 * 4^10 = 10^7 OK
i64 dijkstra(vector<vector<pair<i64, i64>>> &g, i64 src, i64 dest){
	vector<i64> dist(g.size(), INF);
	set<pair<i64, i64>> q;		
	dist[src] = 0;
	q.emplace(0, src);
	while (!q.empty()){
		auto[d, u] = *q.begin();
		q.erase(q.begin());
		// NOTE: this distance is always optimal because of the overwrite
		for (auto[v, w]: g[u]){
			if (dist[u] + w < dist[v]){
				// erase potential old (suboptimal) node waiting in queue
				q.erase(make_pair(dist[v], v));
				dist[v] = dist[u] + w;
				// add optimal counterpart
				q.emplace(dist[v], v);
			}
		}
	}
	return dist[dest];
}

void solve(){
	i64 n, m;
	string src_mask;
	cin >> n >> m;
	cin >> src_mask;

	i64 src = 0, p2 = 1;
	for (i64 i = n - 1; i >= 0; i--){
		src += (i64)(src_mask[i] - '0') * p2;
		p2 = p2 * (i64)2;
	}

	vector<vector<i64>> adj_matrix(1ll << n, vector<i64>(1ll << n, INF));
	// O(m * (n + 2^n))
	for (i64 i = 0; i < m; i++){
		i64 d;
		string u_mask, v_mask;
		cin >> d >> u_mask >> v_mask;
		// directed (mask, (mask & ~u) | v) edge
		// (since removes everything in (mask intersection u) and adds everything in v
		i64 u = 0, v = 0, p2 = 1;
		for (i64 i = n - 1; i >= 0; i--){
			u += (i64)(u_mask[i] - '0') * p2;
			v += (i64)(v_mask[i] - '0') * p2;
			p2 = p2 * (i64)2;
		}
		for (i64 mask = 0; mask < (1ll << n); mask++){
			i64 dest = (mask & ((1ll << n) - 1 - u)) | v;
			adj_matrix[mask][dest] = min(d, adj_matrix[mask][dest]);
		}
	}

	// O(m * 2^n)
	vector<vector<pair<i64, i64>>> g(1ll << n);
	for (i64 u_mask = 0; u_mask < (1ll << n); u_mask++){
		for (i64 v_mask = 0; v_mask < (1ll << n); v_mask++){
			if (adj_matrix[u_mask][v_mask] < INF){
				g[u_mask].emplace_back(v_mask, adj_matrix[u_mask][v_mask]);
			}
		}
	}
	i64 ans = dijkstra(g, src, 0);
	if (ans < INF){
		cout << ans << endl;
	} else {
		cout << -1 << endl;
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
