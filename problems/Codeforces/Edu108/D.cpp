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

void solve(){
	i64 n;
	cin >> n;

	// dp[i][j] = a[j]b[i] + a[j - 1]b[i + 1] + ... + a[i]b[j]
	i64 a[n], b[n], dp[n][n];
	i64 p[n + 1];
	p[0] = 0;
	
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}
	for (i64 i = 0; i < n; i++){
		cin >> b[i];
	}
	for (i64 i = 0; i < n; i++){
		p[i + 1] = p[i] + a[i] * b[i];
	}

	for (i64 i = 0; i < n; i++){
		dp[i][i] = a[i] * b[i];
	}
	for (i64 i = 0; i < n - 1; i++){
		dp[i][i + 1] = a[i + 1] * b[i] + a[i] * b[i + 1];
	}

	for (i64 d = 2; d < n; d++){
		for (i64 i = 0; i + d < n; i++){
			dp[i][i + d] = a[i + d] * b[i] + a[i] * b[i + d] + dp[i + 1][i + d - 1];
		}
	}

	i64 ans = p[n];
	for (i64 i = 0; i < n; i++){
		for (i64 j = i + 1; j < n; j++){
			ans = max(ans, p[i] + dp[i][j] + p[n] - p[j + 1]);
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
