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
// #define printadj(msg, adj) cout << msg; for (i64 u = 0; u < adj.size(); u++) { cout << make_pair(u/n + 1, u % n + 1) << ": "; for (i64 v: adj[u]) { cout << make_pair(v / n + 1, v % n + 1) << "|"; } cout << endl; }
 
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

pair<i64, vector<i64>> bfs(
	const vector<vector<i64>> &g,
	const vector<tuple<i64, i64, i64>> &forbidden,
	const i64 src = 0,
	const i64 dest = 0
){
	auto is_forbidden = [&forbidden](i64 a, i64 b, i64 c){ // O(log k)
		auto it = lower_bound(forbidden.begin(), forbidden.end(), tuple<i64, i64, i64>(a,b,c));
		return (it != forbidden.end() && *it == tuple<i64, i64, i64>(a,b,c));
	};
	vector<vector<i64>> dist(g.size(), vector<i64>(g.size(), INF));
	vector<vector<i64>> prev(g.size(), vector<i64>(g.size(), -1));
	// vector<i64> prev(g.size(), -1);
	queue<tuple<i64, i64, i64>> q;
	q.emplace(src, 0, -1);
	while (!q.empty()){
		auto[u, d, p] = q.front();
		q.pop();
		for (i64 v: g[u]){
			if (dist[u][v] == INF && !is_forbidden(p, u, v)){
				dist[u][v] = d + 1;
				prev[u][v] = p;
				q.emplace(v, d + 1, u);
			}
		}
	}
	pair<i64, i64> last_edge = make_pair(-1, -1);
	i64 ans = INF;
	for (i64 u: g[dest]){
		if (dist[u][dest] < ans){
			ans = dist[u][dest];
			last_edge = make_pair(u, dest);
		}
	}
	vector<i64> path;
	while (last_edge.first != -1 && last_edge.second != -1){
		path.emplace_back(last_edge.second);
		last_edge = make_pair(prev[last_edge.first][last_edge.second], last_edge.first);
	}
	path.emplace_back(0);
	reverse(path.begin(), path.end());
	return {ans, path};
} 

void solve(){
	i64 n, m, k;
	cin >> n >> m >> k;
	
	vector<vector<i64>> g(n);
	// vector<pair<i64, i64>> edges(m);
	for (i64 i = 0; i < m; i++){
		i64 a, b;
		cin >> a >> b;
		--a; --b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	
	vector<tuple<i64, i64, i64>> forbidden(k);
	for (i64 i = 0; i < k; i++){
		i64 a, b, c;
		cin >> a >> b >> c;
		--a; --b; --c; // correct from 1-indexing
		forbidden[i] = {a, b, c};
	} 

	sort(forbidden.begin(), forbidden.end());
	// run bfs
	//
	auto[ans, path] = bfs(g, forbidden, 0, n - 1);
	if (ans == INF){
		cout << -1 << endl;
	} else {
		cout << ans << endl;
		for (i64 x: path){
			cout << x + 1 << " ";
		}
		cout << endl;
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
