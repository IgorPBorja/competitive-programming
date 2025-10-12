// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

/*
dp[m][flag][n]

dp[i][false][j] = how many matches of t[0..j] into s[0..j] with no modified chars
dp[i][true][j] = how many matches of t[0..j] into s[0..j] with no modified chars
*/

const i64 MOD = (i64)1e9 + 7;

void solve(){
    i64 n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;

    i64 dp[m][2][n];
    dp[0][0][0] = (t[0] == s[0]);
    dp[0][1][0] = (t[0] != s[0]);
    for (i64 j = 1; j < n; j++) {
        // match now or before with zero mods
        dp[0][0][j] = (dp[0][0][j - 1] + (t[0] == s[j])) % MOD;

        // mod before, match before
        dp[0][1][j] = dp[0][1][j - 1];
        // mod now, match before
        dp[0][1][j] = (dp[0][1][j] + 25 * dp[0][0][j - 1]) % MOD;
        // mod before, match now
        if (t[0] == s[j]) dp[0][1][j] = (dp[0][1][j] + 25 * j) % MOD;
        // mod now, match now
        if (t[0] != s[j]) dp[0][1][j] = (dp[0][1][j] + 1) % MOD;
    }
    for (i64 i = 1; i < m; i++){
        for (i64 j = 0; j < i; j++) {
            dp[i][0][j] = dp[i][1][j] = 0;  // too small
        }
        for (i64 j = i; j < n; j++){
            // base values: match is before i
            dp[i][0][j] = dp[i][0][j - 1];
            // try no modifications
            if (t[i] == s[j]){
                dp[i][0][j] = (dp[i][0][j] + dp[i - 1][0][j - 1]) % MOD;
            }

            // mod before, match before
            dp[i][1][j] = dp[i][1][j - 1];
            // mod now, match before
            dp[i][1][j] = (dp[i][1][j - 1] + 25 * dp[i][0][j - 1]) % MOD;
            // mod before, match now
            if (t[i] == s[j]){
                dp[i][1][j] = (dp[i][1][j] + dp[i - 1][1][j - 1]) % MOD;
            }
            // mod now, match now
            if (t[i] != s[j]){
                dp[i][1][j] = (dp[i][1][j] + dp[i - 1][0][j - 1]) % MOD;
            }
        }
    }
    // for (i64 i = 0; i < m; i++){
    //     for (i64 b = 0; b < 2; b++){
    //         cerr << "dp[" << i << "][" << b << "]=";
    //         for (i64 j = 0; j < n; j++) cerr << dp[i][b][j] << " ";
    //         cerr << endl;
    //     }
    // }
    i64 ans = (dp[m - 1][0][n - 1] + dp[m - 1][1][n - 1]) % MOD;
    cout << ans << endl;
}
 
signed main(){
	fastio;
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
