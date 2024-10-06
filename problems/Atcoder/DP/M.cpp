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
    dp[i][j] number of ways to share j candies between i children
    dp[0][0] = 1, dp[0][x] = 0 for x > 0

    dp[i][j] = sum(k <= a[i]) dp[i - 1][j - k]  ==> naive implementation is O(NK^2)

    Define dp'[i][j] = sum(j' <= j) dp[i][j']

    Then dp'[i][j] = dp'[i][j - 1] + dp[i][j] = dp'[i][j - 1] + dp'[i - 1][j] - dp'[i - 1][j - a[i] - 1]
    now the transitions are O(1) and final complexity is O(NK)
*/

const i64 MOD = (i64)1e9 + 7;

void solve(){
    i64 n, k;
    cin >> n >> k;
    i64 a[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    i64 dp[n + 1][k + 1];
    dp[0][0] = 1;
    for (i64 i = 1; i <= k; i++){
        dp[0][i] = dp[0][i - 1] + 0;   // remember this dp is prefixed for optimization
    }
    for (i64 i = 1; i <= n; i++){
        dp[i][0] = 1;
        for (i64 j = 1; j <= k; j++){
            dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % MOD;
            if (a[i - 1] < j){
                // children i gets x with j >= x >= a[i] + 1
                dp[i][j] = (dp[i][j] + (MOD - dp[i - 1][j - a[i - 1] - 1])) % MOD;
            }
        }
    }
    // for (i64 i = 0; i <= n; i++){
    //     string msg = "dp[" + to_string(i) + "]=";
    //     printmsg(msg, dp[i], dp[i] + k + 1);
    // }
    i64 ans = dp[n][k];
    if (k > 0){
        ans = (ans + (MOD - dp[n][k - 1])) % MOD;
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
