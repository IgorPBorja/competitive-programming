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

const i64 MAXN = 5e4, MAXK = 500;
i64 dp[MAXN][MAXK + 3];

void solve(){
	i64 n, k;
	cin >> n >> k;
	vector<vector<i64>> tree(n), dag(n);	
	for (i64 i = 0; i < n - 1; i++){
		i64 a, b;
		cin >> a >> b;
		--a; --b;
		tree[a].emplace_back(b);
		tree[b].emplace_back(a);
	}

	vector<i64> depth(n, -1);
	vector<vector<i64>> per_depth(n);
	queue<pair<i64, i64>> q;
	q.emplace(0, 0);
	while (!q.empty()){
		auto[d,u] = q.front();
		q.pop();
		if (depth[u] != -1) continue;
		depth[u] = d;
		per_depth[d].emplace_back(u);
		for (i64 v: tree[u]){
			if (depth[v] == -1){
				dag[u].emplace_back(v);
				q.emplace(d + 1, v);
			}
		}
	}

	// printmsg("depth=", depth.begin(), depth.end());
	for (i64 d = n - 1; d >= 0; d--){
		// printmsg("per_depth[" << d << "]=", per_depth[d].begin(), per_depth[d].end());
		for (i64 u: per_depth[d]){
			dp[u][0] = 1;
			for (i64 a = 1; a <= MAXK + 1; a++){
				dp[u][a] = 0;
				for (i64 v: dag[u]){
					dp[u][a] += dp[v][a - 1];
				}
			}
		}
	}

	// for (i64 u = 0; u < n; u++) { printmsg("dp[" << u << "]=", dp[u], dp[u] + sizeof(dp[u]) / sizeof(i64)) } ;

	i64 ans = 0;
	for (i64 u = 0; u < n; u++){
		// sum(a=1...k-1) sum(i-> i1 != i2) dp[i1][a - 1] * dp[i2][k - 1 - a]
		// + dp[i][k]
		// = dp[i][k] + sum(a=1...k - 1) [ (sum(i1) dp[i1][a - 1])) * (sum(i2) dp[i2][k - 1 - a]) - sum(i1) dp[i1][a - 1] * dp[i1][k - 1 - a] ]
		// dp[i][k] + sum(a=1...k-1) dp[i][a] * dp[i][k - a] - sum(a=1...k-1)sum(i -> i1)dp[i1][a - 1] * dp[i1][k - 1 - a]
		// sum(a=0...k-1) dp[i][a] * dp[i][k - a] - sum(a=1...k-1)sum(i->i1)dp[i1][a-1] * dp[i1][k - 1 - a]
		i64 partial = 2 * dp[u][k];
		for (i64 a = 1; a <= k - 1; a++){
			partial += dp[u][a] * dp[u][k - a];
			for (i64 v: dag[u]){
				partial -= dp[v][a - 1] * dp[v][k - 1 - a];
			}
		}
		partial >>= 1ll; // double counting
		ans += partial;
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
