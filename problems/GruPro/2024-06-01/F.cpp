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


void connected(i64 u, size_t c, vector<vector<i64>> &g, vector<vector<i64>> &components, vector<bool> &vis){
	if (!vis[u]){
		if (components.size() <= c) components.emplace_back(vector<i64>());
		components[c].emplace_back(u);
		vis[u] = true;
		for (i64 v: g[u]) connected(v, c, g, components, vis);
	}
}

void solve(){
	i64 n, m;
	cin >> n >> m;

	vector<vector<i64>> g(n), components;
	vector<bool> vis(n, false);
	for (i64 i = 0; i < m; i++){
		i64 a, b;
		cin >> a >> b;
		--a; --b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}

	for (i64 i = 0; i < n; i++){
		connected(i, components.size(), g, components, vis);
	}

	i64 cycle_cnt = 0;
	for (vector<i64> c: components){
		bool is_cycle = true;
		for (i64 u: c) {
			is_cycle = is_cycle && (g[u].size() == 2);
		}
		if (is_cycle){
			++cycle_cnt;
		}
	}
	cout << cycle_cnt << endl;
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
