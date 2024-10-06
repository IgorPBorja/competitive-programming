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
	i64 n, m, k, d;
	cin >> n >> m >> k >> d;
      	i64 a[n][m];
	i64 dp[m], mx[n];

      	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < m; j++){
			cin >> a[i][j];
		}
	}

	for (i64 i = 0; i < n; i++){
		multiset<i64> last_d;
		memset(dp, 0, sizeof dp);
		dp[0] = 1;
		last_d.insert(dp[0]);
		for (i64 j = 1; j <= min(d + 1, m - 1); j++){
			dp[j] = a[i][j] + 1 + dp[0];
			last_d.insert(dp[j]);
		}
		// j - 0 - 1 <= d ==> j <= d + 1
		for (i64 j = d + 2; j < m; j++){
			auto it_first = last_d.find(dp[j - d - 2]);
			// erase FIRST ocurrence only, which explains erasing by iterator instead of key
			last_d.erase(it_first); // since |j - (j - d - 2)| - 1 = d + 1 > d
			i64 best = *last_d.begin();
			dp[j] = best + a[i][j] + 1;
			last_d.insert(dp[j]);
		}
		mx[i] = dp[m - 1];
	}

	i64 ans, cur = 0;
	for (i64 i = 0; i < k; i++){
		cur += mx[i];
	}
	ans = cur;
	for (i64 i = k; i < n; i++){
		cur -= mx[i - k];
		cur += mx[i];
		ans = min(ans, cur);
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
