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
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

const i64 MOD = (i64)1e9 + 7;

void solve(){
	i64 n;
	cin >> n;

	i64 adj[n][n];
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < n; j++){
			cin >> adj[i][j];
		}
	}

	// subpoly (i,...,j) where (i,j) already connected
	vector<vector<i64>> dp_con(n, vector<i64>(n));
	// subpoly (i,...,j) where (i,j) WON'T be connected
	vector<vector<i64>> dp_empty(n, vector<i64>(n));

	for (i64 i = 0; i < n; i++){
		dp_con[i][i] = 0;  // can't connect i to itself
		dp_empty[i][i] = 1;
	}
	// brute force dp[i][i + 1] as 0 if edge is allowed else 1
	for (i64 i = 0; i < n; i++){
		dp_con[i][(i + 1) % n] = adj[i][(i + 1) % n];
		dp_empty[i][(i + 1) % n] = adj[i][(i + 1) % n];
	}

	for (i64 s = 3; s <= n; s++){
		for (i64 i = 0; i < n; i++){
			const i64 _j = i + s - 1;
			const i64 j = _j % n;
			dp_con[i][j] = 0;
			dp_empty[i][j] = 0;

			for (i64 _k = i + 1; _k < _j; _k++){
				const i64 k = _k % n;

				// for dp_con
				// let k be the largest element i connects to in (i+1,...j-1)
				// then subpoly (i...k) has solution dp_con[i][k]
				// but for subpoly (k+1...j) we can either have it alone or have k connect to it
				// (so either dp_empty[k][j] or dp_empty[k+1][j])

				const i64 delta_con = (dp_con[i][k] * ((dp_empty[k][j] + dp_empty[(k + 1) % n][j]) % MOD)) % MOD;
				dp_con[i][j] = (dp_con[i][j] + delta_con) % MOD;

				// for dp_empty:
				// let k be the largest element i connects to in (i+1,...j-1)
				// then subpoly (i...k) has solution dp_con[i][k]
				// and subpoly (k...j) has only solution dp_empty[k][j]
				const i64 delta_empty = (dp_con[i][k] * dp_empty[k][j]) % MOD;
				dp_empty[i][j] = (dp_empty[i][j] + delta_empty) % MOD;
			}
		}
	}

	printgraph("dp_con=", dp_con);
	printgraph("dp_empty=", dp_empty);
	
	// ans = dp_con[1][0] + dp_empty[1][0] since we can either have (0,1) connected or not
	cout << (dp_con[1][0] + dp_empty[1][0]) % MOD << endl;
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
