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


// using the shortest path is always best
// since we can just wait to get the same time as the "no waiting" solution
// usual dijkstra, with dynamic weights

const i64 INF = (i64)2e18;

void solve(){
    i64 n, m, t;
    cin >> n >> m >> t;
    vector<vector<tuple<i64, i64, i64>>> adj(n);
    for (i64 i = 0; i < m; i++){
        i64 a, b, x, y;
        cin >> a >> b >> x >> y;
        --a; --b;
        adj[a].emplace_back(b, x, y);
        adj[b].emplace_back(a, x, y);
    }

    min_pq<pair<i64, i64>> pq;
    vector<i64> dist(n, INF);
    pq.emplace(0, 0);
    while (!pq.empty()){
        auto[d, u] = pq.top();
        pq.pop();
        if (d >= dist[u]) continue;
        dist[u] = d;
        for (auto[v, x, y]: adj[u]){
            i64 r = (d + t) % (x + y);
            i64 waiting_time = (r >= x ? y - (r - x) : (i64)0);
            if (d + waiting_time < dist[v]){
                // debug << "improved v=" << v << " from u=" << u << endl;
                pq.emplace(d + waiting_time, v);
            }
        }
    }
    cout << t + dist[n - 1] << endl;
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
