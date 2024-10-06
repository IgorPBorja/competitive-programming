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
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
 
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

const i64 INF = 2e18;

vector<i64> dijkstra(vector<vector<pair<i64, i64>>> &g, i64 src){
	vector<i64> dist(g.size(), INF);
	min_pq<pair<i64, i64>> q;
	q.emplace(0, src);
	while (!q.empty()){
		auto[d, u] = q.top();
		q.pop();
		if (d >= dist[u]) continue;
		dist[u] = d;
		for (auto[v, w]: g[u]){
			if (dist[u] + w < dist[v]){
				q.emplace(dist[u] + w, v);
			}
		}
	}
	return dist;
}

void solve(){
	i64 n, m, k;
	cin >> n >> m >> k;

	vector<vector<pair<i64, i64>>> g(n);
	map<pair<i64, i64>, i64> general;
	i64 a, b, c;
	for (i64 i = 0; i < m; i++){
		cin >> a >> b >> c;
		--a; --b;  // to 0-index
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
		if (a == 0){
			++general[make_pair(b, c)];
		}
		if (b == 0){
			++general[make_pair(a, c)];
		}
	}

	// vector<i64> dist_no_trains = dijkstra(g, 0);

	map<pair<i64, i64>, i64> train_routes;
	for (i64 i = 0; i < k; i++){
		cin >> b >> c;
		--b;  // to 0-index
		++train_routes[make_pair(b, c)];
		g[0].emplace_back(b, c);
		g[b].emplace_back(0, c);
	}

	vector<i64> dist = dijkstra(g, 0);
	vector<i64> indirect_dist(n);
	indirect_dist[0] = 0;
	for (i64 s = 1; s < n; s++){
		indirect_dist[s] = INF;
		for (auto[t, w]: g[s]){
			if (t == 0) continue;
			indirect_dist[s] = min(indirect_dist[s], dist[t] + w);
		}
	}
	i64 can_remove = 0;

	// edge (0,s) is in some shortest path from 0 iff it is the shortest path to s itself
	for (auto[p, cnt]: train_routes){
		if (p.second > dist[p.first]){
			can_remove += cnt;
		} else {
			// it is optimal ==> remove all duplicates except one
			// UNLESS there is indirect path which is good
			// or a non-train direct edge
			if ((indirect_dist[p.first] == dist[p.first]) || (general[p] > 0)){
				can_remove += cnt;
			} else {
				can_remove += max(cnt - 1, (i64)0);
			}
		}
	}
	cout << can_remove << endl;
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
