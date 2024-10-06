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

const i64 MAXN = 500;
const i64 INF = 1e18;
i64 dp[MAXN + 1][MAXN + 1];

void solve(){
    for (i64 i = 1; i <= MAXN; i++){
        for (i64 j = 1; j <= MAXN; j++){
            dp[i][j] = INF;
        }
    }

    for (i64 i = 1; i <= MAXN; i++){
        for (i64 j = 1; j <= MAXN; j++){
            if (i == j){
                dp[i][j] = 0;
                continue;
            }
            // vertical cuts
            for (i64 j2 = 1; j2 < j; j2++){
                dp[i][j] = min(dp[i][j], (i64)1 + dp[i][j2] + dp[i][j - j2]);
            }
            // horizontal cuts
            for (i64 i2 = 1; i2 < i; i2++){
                dp[i][j] = min(dp[i][j], (i64)1 + dp[i2][j] + dp[i - i2][j]);
            }
        }
    }

    i64 a, b;
    cin >> a >> b;
    cout << dp[a][b] << endl;
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
