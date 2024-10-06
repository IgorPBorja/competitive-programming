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
Represent each dish i by an edge (2i -- 2i + 1) with weight a[i]
Represent each connection/eating rule (i, j, c) by an edge (2i + 1, 2j) with weight c

We have k + n = O(n^2) edges and O(n) vertices

Run Floyd-warshall in O(m * n^2) to know the maximum path using 2m - 1 edges

node 1 --> node 2 --> ... --> node m
m internal edges, m - 1 external edges
*/

/*
Idea 2: dp[mask][k] = maximum satisfaction eating the subset given by mask ending a dish k

dp[mask | 1 << j][j] = max_i(dp[mask][i] + rule[i][j] + a[j]) for each i in mask
==> O(2^n * n) dp with O(n) transition
==> 2^18 * 18^2 < 10^6 * 400 / 4 = 10^8
*/
const i64 INF = 1e15;

void solve(){
	i64 n, m, k;
	cin >> n >> m >> k;

	i64 a[n], rules[n][n];
	i64 dp[1ll << n][n];
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < n; j++){
			rules[i][j] = 0;
		}
	}
	for (i64 mask = 0; mask < (1ll << n); mask++) {
		for (i64 i = 0; i < n; i++) {
			dp[mask][i] = -INF;
		}
	}

	// start solving!
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	for (i64 i = 0; i < k; i++){
		i64 a, b, c;
		cin >> a >> b >> c;
		--a; --b;
		rules[a][b] = c;
	}

	// loop invariant: mask has one less active bit than mask | (1ll << j)
	for (i64 mask = 0; mask < (1ll << n); mask++){
		// if (__builtin_popcount(mask) == 1) continue;
		for (i64 j = 0; j < n; j++){  // add dish j to mask
			if (mask & (1ll << j)) continue;
			i64 best = 0;
			for (i64 i = 0; i < n; i++){
				if (mask & (1ll << i)) {
					best = max(best, dp[mask][i] + rules[i][j]);
				}
			}
			dp[mask | (1ll << j)][j] = best + a[j];
		}
	}
	i64 best = 0;
	for (i64 mask = 0; mask < (1ll << n); mask++){
		if (__builtin_popcount(mask) != m) continue;
		for (i64 i = 0; i < n; i++){
			best = max(best, dp[mask][i]);
		}
	}
	cout << best << endl;
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
