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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

typedef vector<vector<pair<i64, i64>>> weighted_graph;
typedef priority_queue<pair<i64, i64>, vector<pair<i64, i64>>, greater<pair<i64, i64>>> min_node_pq;
const i64 INF = 1e18;

multiset<i64, greater<i64>> k_dijkstra(weighted_graph g, i64 k, i64 s, i64 t){
	vector<multiset<i64, greater<i64>>> k_dist(g.size());
	for (auto& m: k_dist){
		m.emplace(INF);
	}
	min_node_pq q;
	
	q.emplace(0, s);
	while (!q.empty()){
		auto [d, u] = q.top();
		q.pop();
		i64 last = *k_dist[u].begin();
		if (d >= last){
			continue; // not k-optimal
		}
		if (k_dist[u].size() == k){ // too full
			k_dist[u].erase(k_dist[u].begin());
		}
		k_dist[u].insert(d);
		for (auto[delta, v]: g[u]){
			last = *k_dist[v].begin();
			if (d + delta < last){
				q.emplace(d + delta, v);
			}
		}
	}
	return k_dist[t];
}

void solve(){
	i64 n, m, k;
	cin >> n >> m >> k;

	weighted_graph g(n);
	for (i64 i = 0; i < m; i++){
		i64 a, b, c;
		cin >> a >> b >> c;
		--a; --b;
		g[a].emplace_back(c, b);
	}

	multiset<i64, greater<i64>> k_dist = k_dijkstra(g, k, 0, n - 1);
	for (multiset<i64, greater<i64>>::reverse_iterator it = k_dist.rbegin(); it != k_dist.rend(); it++){
		cout << *it << " ";
	}
	cout << endl;
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
