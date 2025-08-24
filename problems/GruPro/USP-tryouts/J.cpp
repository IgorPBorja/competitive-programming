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

const i64 INF = (i64)1e18;
const i64 MOD = (i64)1e9 + 7;

pair<vector<i64>, vector<i64>> bfs(const vector<vector<i64>>& adj, i64 s){
    const i64 n = adj.size();
    vector<i64> d(n, INF), cnt(n, 0);
    queue<tuple<i64, i64, i64>> q;
    q.emplace(s, 0, -1);

    cnt[s] = 1;
    while (!q.empty()){
        auto[u, cur_d, p] = q.front();
        q.pop();
        if (d[u] == INF || d[u] == cur_d){
            // record time path
            if (p != -1) {  // excludes starting path empty -> s
                cnt[u] = (cnt[u] + cnt[p]) % MOD; 
            }
        }
        if (d[u] <= cur_d) continue;
        d[u] = cur_d;
        for (i64 v: adj[u]){
            if (d[v] == INF){
                // is record path
                q.emplace(v, cur_d + 1, u);
            }
        }
    }
    return {d, cnt};
}

void solve(){

    i64 n, m, s, t;
    cin >> n >> m >> s >> t;
    --s; --t;
    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < m; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    auto[ds, cnt_s] = bfs(adj, s);
    auto[dt, cnt_t] = bfs(adj, t);

    i64 total = 0;
    for (i64 pivot = 0; pivot < n; pivot++){
        if (ds[pivot] + dt[pivot] > ds[t]){
            continue;
        }
        for (i64 v: adj[pivot]){
            if (ds[pivot] + dt[v] == ds[t]){
                total = (total + cnt_s[pivot] * cnt_t[v]) % MOD;
            }
        }
    }
    cout << total << endl;
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
