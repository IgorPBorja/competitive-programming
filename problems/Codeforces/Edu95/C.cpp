#define TESTCASES
// #define MYDEBUG
 
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
	i64 n;
	cin >> n;
	vector<i64> a(n);
	for (i64 i = 0; i < n; i++) cin >> a[i];

	i64 dp[n][2];
	dp[0][1] = a[0]; dp[0][0] = 1e18; // can't kill boss 1 with player 0, since player 1 starts
	if (n > 1){
		dp[1][0] = dp[0][1]; dp[1][1] = a[0] + a[1];
	}
	for (i64 i = 2; i < n; i++){
		dp[i][0] = min(dp[i - 1][1], dp[i - 2][1]);
		dp[i][1] = min(dp[i - 1][0] + a[i], dp[i - 2][0] + a[i - 1] + a[i]);
	}
	cout << min(dp[n - 1][0], dp[n - 1][1]) << endl;
}
 
signed main(){
	fastio;
#ifdef MYDEBUG
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
