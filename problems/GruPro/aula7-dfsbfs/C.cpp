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

// i64 bfs01(vector<vector<i64>> &g, vector<i64> &cats, i64 src, i64 m){
// 	struct Node {
// 		i64 p, v, cost_v;
// 		Node(i64 p, i64 v, i64 cost_v) : p(p), v(v), cost_v(cost_v) {}
// 	};
// 	const i64 INF = 1e18;
// 	vector<i64> cost(g.size(), INF);
// 	deque<Node> q;
// 	q.emplace_back(Node(-1, src, cats[src]));
// 	while (!q.empty()){
// 		Node n = q.front();
// 		q.pop_front();
// 		if (((n.p >= 0) ? cost[n.p] : 0) + n.cost_v >= cost[n.v]){
// 			continue;
// 		}
// 		cost[n.v] = ((n.p >= 0) ? cost[n.p] : 0) + n.cost_v;
// 		for (i64 u: g[n.v]){
// 			if (cats[u] == 0){
// 				q.push_front(Node(n.v, u, cats[u]));
// 			} else {
// 				q.push_back(Node(n.v, u, cats[u]));
// 			}
// 		}
// 	}
// 	print(cost);
// 	i64 cnt = 0;
// 	for (i64 u = 0; u < g.size(); u++){
// 		if (u != src && g[u].size() == 1 && cost[u] <= m){
// 			// cheap node
// 			++cnt;
// 		}
// 	}
// 	return cnt;
// }
const i64 INF = 1e18;

void solve(){
	i64 n, m;
	cin >> n >> m;

	vector<i64> cats(n);
	vector<vector<i64>> g(n);
	for (i64 i = 0; i < n; i++){
		cin >> cats[i];
	}
	for (i64 i = 0; i < n - 1; i++){
		i64 a, b;
		cin >> a >> b;
		--a; --b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}

	// do dp (since it is a rooted tree)
	vector<i64> dp(n);
	vector<bool> valid(n, false);
	queue<tuple<i64, i64, i64>> q;
	q.emplace(-1, 0, 0);
	while (!q.empty()){
		auto[parent, u, c] = q.front();
		q.pop();
		if (cats[u] > 0){
			dp[u] = c + cats[u];
		} else {
			dp[u] = 0;  // streak broken
		}
		if (dp[u] > m){
			// too large, truncate subtree
			continue;
		}
		valid[u] = true;
		for (i64 v: g[u]){
			if (v != parent){
				q.emplace(u, v, dp[u]);
			}
		}
	}

	// count leafs (except root, vertex 0) where the path has <= m consecutive cats
	i64 cnt = 0;
	for (i64 i = 1; i < n; i++){
		if (g[i].size() == 1 && valid[i]) ++cnt;
	}
	cout << cnt << endl;
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
