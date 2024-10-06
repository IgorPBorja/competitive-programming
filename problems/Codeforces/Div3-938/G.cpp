#define TESTCASES
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

void solve(){
	i64 n, m;	
	cin >> n >> m;
	vector<vector<i64>> grid(n, vector<i64>(m));
	vector<vector<i64>> dp(n, vector<i64>(m, false));

	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < m; j++){
			cin >> grid[i][j];
		}
	}
	i64 mx = 1;
	i64 a = grid[0][0];
	a = __gcd(a, grid[n - 1][m - 1]);
	for (i64 d = 1; d * d <= a; d++){
		if (a % d != 0) continue;
		for (i64 i = 0; i < n; i++){
			for (i64 j = 0; j < m; j++){
				dp[i][j] = (grid[i][j] % d == 0) ? 1 : 0;
			}
		}
		for (i64 j = 1; j < m; j++){
			dp[0][j] &= dp[0][j - 1];
		}
		for (i64 i = 1; i < n; i++){
			dp[i][0] &= dp[i - 1][0];
			for (i64 j = 1; j < m; j++){
				dp[i][j] &= (dp[i - 1][j] | dp[i][j - 1]);
			}
		}
		if (dp[n - 1][m - 1] > 0) mx = max(mx, d);

		if (a / d  == d) continue;
		for (i64 i = 0; i < n; i++){
			for (i64 j = 0; j < m; j++){
				dp[i][j] = (grid[i][j] % (a / d) == 0) ? 1 : 0;
			}
		}
		for (i64 j = 1; j < m; j++){
			dp[0][j] &= dp[0][j - 1];
		}
		for (i64 i = 1; i < n; i++){
			dp[i][0] &= dp[i - 1][0];
			for (i64 j = 1; j < m; j++){
				dp[i][j] &= (dp[i - 1][j] | dp[i][j - 1]);
			}
		}
		if (dp[n - 1][m - 1] > 0) mx = max(mx, a/d);
	}
	cout << mx << endl;
}
 
signed main(){
	fastio;
// #ifdef DEBUG
// 	freopen("/tmp/in", "r", stdin);
// #endif
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
