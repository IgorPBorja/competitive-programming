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

const i64 INF = 2e18;

void solve(){
    string s, t;
    cin >> s >> t;
    const i64 n = s.size(), m = t.size();

    vector<vector<i64>> dp(n + 1, vector<i64>(m + 1, INF));

    for (i64 j = 0; j <= m; j++){
        // add entire t[j...m-1]
        dp[n][j] = m - j;
    }
    for (i64 i = n - 1; i >= 0; i--){
        // add entire s[i...n-1]
        dp[i][m] = n - i;
        for (i64 j = m - 1; j >= 0; j--){
            dp[i][j] = min(
                dp[i + 1][j + 1] + ((s[i] == t[j]) ? 0 : 1), // replace
                min(
                    1 + dp[i][j + 1], // remove from t
                    1 + dp[i + 1][j] // remove from s
                )
            );
        }
    }
    cout << dp[0][0] << endl;
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
