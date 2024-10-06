//#define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define i64 int64_t
#define endl '\n'

#define ep emplace
#define eb emplace_back

void solve(){
	i64 n;
	cin >> n;
	vector<i64> a(n);
    	for (i64 i = 0; i < n; i++) cin >> a[i];
	
	vector<vector<i64>> dp(n, vector<i64>(n + 1, -1e18)); // dp[i][j] = max health when grabbing j potions ending at i with 0 health
	dp[0][0] = 0;
	dp[0][1] = a[0];
	for (i64 i = 1; i < n; i++){
	    dp[i][0] = 0;
	    for (i64 j = i + 2; j <= n; j++) dp[i][j] = -1e18;
	    for (i64 j = 1; j <= i + 1; j++){
		if ((dp[i - 1][j - 1] >= 0 && dp[i - 1][j - 1] + a[i] >= 0)){
			dp[i][j] = max(dp[i - 1][j - 1] + a[i], dp[i - 1][j]);
		}
		else {
			dp[i][j] = dp[i - 1][j];
		}
	    }
	}

	for (i64 j = n; j >= 0; j--){
	    if (dp[n - 1][j] >= 0){
	        cout << j << endl;
	        return;
	    }
	}
	cout << 0 << endl;
}

signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--) solve();
}
