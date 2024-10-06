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

	vector<i64> a(n), b(n);
	vector<i64> dp[2], dp_r[2];
	for (i64 i = 0; i < 2; i++){
		dp[i].assign(n, 0);
		dp_r[i].assign(n, 0);
	}

	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}
	for (i64 i = 0; i < n; i++){
		cin >> b[i];
	}
	i64 ans = 0;

	// dp rev
	dp_r[(n - 1) % 2][n - 1] = a[n - 1] * b[n - 1];
	for (i64 i = n - 2; i >= 0; i--){
		dp[i % 2][i] = a[i] * b[i];
		for (i64 j = i + 1; j < n; j++){
			dp[i % 2][j] = dp[i % 2][j - 1] + a[j] * b[j];
		}
		dp_r[i % 2][i] = a[i] * b[i];
		dp_r[i % 2][i + 1] = a[i] * b[i + 1] + a[i + 1] * b[i];
		for (i64 j = i + 2; j < n; j++){
			dp_r[i % 2][j] = a[i] * b[j] + a[j] * b[i] + dp_r[(i + 1) % 2][j - 1];
		}
		for (i64 j = i; j < n; j++){
			ans = max(ans, dp_r[i % 2][j] - dp[i % 2][j]);
		}
	}

	i64 s = 0;
	for (i64 i = 0; i < n; i++){
		s += a[i] * b[i];
	}
	cout << ans + s << endl;
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

