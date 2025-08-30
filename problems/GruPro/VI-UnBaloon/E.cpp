// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
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

const i64 MOD = (i64)1e9 + 7;

void solve(){
    // starting at char c, can go to 0..c+1

    i64 n;
    cin >> n;
    vector<vector<i64>> dp(n + 1, vector<i64>(26));
    
    dp[1][0] = 1;
    for (i64 i = 1; i < 26; i++){
        dp[1][i] = 0;
    }
    for (i64 k = 2; k <= n; k++){
        for (i64 c = 0; c < 26; c++){
            if (k < c + 1){
                // can't use c chars
                dp[k][c] = 0;
            } else if (c == 0) {
                dp[k][c] = 1;
            } else {
                // either has already used c ==> 0..c as options
                // or has not used c so c is forced
                // except in the case c=0 where only one option exists
                dp[k][c] = (dp[k - 1][c] * (c + 1) + dp[k - 1][c - 1]) % MOD;
            }
        }
    }
    // printmsg("dp[n]=", dp[n].begin(), dp[n].end());
    i64 ans = 0;
    for (i64 c = 0; c < 26; c++){
        ans = (ans + dp[n][c]) % MOD;
    }
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
