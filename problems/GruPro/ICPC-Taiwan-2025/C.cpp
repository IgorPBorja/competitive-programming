#define TESTCASES
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

void solve(){
    i64 n, m;
    cin >> n >> m;

    if (m == 0){
        cout << 0 << endl;
        return;
    }
    vector<vector<pair<i64, i64>>> adj(n);
    vector<tuple<i64, i64, i64>> shafts(m);
    vector<pair<i64, i64>> shaft_ptrs(m);
    
    for (i64 d = 0; d < m; d++){
        i64 a, b, v;
        cin >> a >> b >> v;
        --a; --b;
        if (a > b) swap(a, b);
        adj[a].emplace_back(d, b);
        adj[b].emplace_back(d, a);
        shafts[d] = make_tuple(a, b, v);
    }
    for (i64 i = 0; i < n; i++){
        sort(all(adj[i]));
        for (i64 idx = 0; idx < adj[i].size(); idx++){
            auto[d, j] = adj[i][idx];
            if (i < j) shaft_ptrs[d].first = idx;
            else shaft_ptrs[d].second = idx;
        }
    }

    vector<i64> dp[2];  // using tunnel at depth d, starting from small/large vertex idx
    dp[0].resize(m); dp[1].resize(m);
    dp[0][m - 1] = dp[1][m - 1] = get<2>(shafts[m - 1]);
    for (i64 d = m - 2; d >= 0; d--){
        auto[a, b, v] = shafts[d];
        // a -> b
        dp[0][d] = v;
        if (shaft_ptrs[d].second + 1 < adj[b].size()){
            auto[d2, _] = adj[b][shaft_ptrs[d].second + 1];
            // at depth d2, is b largest vertex or smallest?
            auto[x, y, __] = shafts[d2];
            if (b == x) dp[0][d] += dp[0][d2];
            else dp[0][d] += dp[1][d2];
        }
        // b -> a
        dp[1][d] = v;
        if (shaft_ptrs[d].first + 1 < adj[a].size()){
            auto[d2, _] = adj[a][shaft_ptrs[d].first + 1];
            // at depth d2, is a largest vertex or smallest?
            auto[x, y, __] = shafts[d2];
            if (a == x) dp[1][d] += dp[0][d2];
            else dp[1][d] += dp[1][d2];
        }
    }
    // print("dp[0]=", dp[0]);
    // print("dp[1]=", dp[1]);
    // print("shaft_ptrs=", shaft_ptrs);

    i64 ans = 0;
    for (i64 i = 0; i < n; i++){
        if (adj[i].empty()) continue;
        // use first shaft
        auto[d, j] = adj[i][0];
        if (i < j) ans = max(ans, dp[0][d]);
        else ans = max(ans, dp[1][d]);
    }
    cout << ans << endl;
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
