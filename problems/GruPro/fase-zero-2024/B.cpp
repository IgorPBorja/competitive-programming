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

const i64 MAXC = 8760;

vector<vector<i64>> build(vector<pair<i64, i64>> edges[MAXC + 1], i64 c, i64 n){
	vector<vector<i64>> g(n);
	for (i64 i = 0; i <= c; i++){
		for (auto[u, v]: edges[i]){
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
	}
	return g;
}

i64 bfscnt(vector<vector<pair<i64, i64>>> &g, i64 c, i64 src = 0){
	queue<i64> q;
	vector<i64> vis(g.size(), 0);
	q.emplace(src);
	while (!q.empty()){
		i64 u = q.front();
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto[edge_c, v]: g[u]){
			if (edge_c > c) break; 
			if (vis[v] == 0) q.emplace(v);
		}
	}
	return accumulate(vis.begin(), vis.end(), 0);
}

void solve(){
	i64 n, m, k;	

	cin >> n >> m >> k;
	vector<vector<pair<i64, i64>>> g(n);

	for (i64 i = 0; i < m; i++){
		i64 a, b, c;
		cin >> a >> b >> c;
		--a; --b;
		g[a].emplace_back(c, b);
		g[b].emplace_back(c, a);
	}
	for (i64 i = 0; i < n; i++){
		sort(g[i].begin(), g[i].end());
	}

	i64 l = 0, r = MAXC, ans = MAXC;
	while (l <= r){
		i64 c = l + (r - l) / 2;
		i64 cnt = bfscnt(g, c);
		if (cnt >= k){
			ans = c;
			r = c - 1;
		} else {
			l = c + 1;
		}
	}
	cout << ans << endl;
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
