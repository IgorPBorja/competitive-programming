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

/*
dp[n][k] = min number of edges using at most k weight going to n
*/
const i64 MAXN = 1e5, MAXK = 100;
const i64 INF = 1e18;
i64 dp[MAXN + 1][2 * MAXK + 1];

void bfs(vector<vector<pair<i64, i64>>> &g, i64 k){
	for (i64 n = 1; n < MAXN; n++){
		for (i64 c = 0; c <= 2 * MAXK; c++){
			dp[n][c] = INF;
		}
	}
	for (i64 c = MAXK + 1; c <= 2 * MAXK; c++){
		dp[0][c] = INF;
	}

	queue<pair<i64, i64>> q;	
	q.emplace(0, 0);
	vector<bool> vis(g.size(), false);
	while (!q.empty()){
		auto[d, u] = q.front();	
		q.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (auto[v, w]: g[u]){
			for (i64 c = 0; c <= k; c++){
				dp[v][c + w] = min(dp[v][c + w], dp[u][c] + 1);
			}
			if (!vis[v]){
				q.emplace(d + 1, v);
			}
		}
	}
}

void solve(){
	i64 n, m, k;
	cin >> n >> m >> k;
	vector<vector<pair<i64, i64>>> g(n);

	for (i64 i = 0; i < m; i++){
		i64 a, b, c;
		cin >> a >> b >> c;
		--a; --b;
		g[a].emplace_back(b, c);
	}
	bfs(g, k);

	if (dp[n - 1][k] < INF){
		cout << dp[n - 1][k] << endl;
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
