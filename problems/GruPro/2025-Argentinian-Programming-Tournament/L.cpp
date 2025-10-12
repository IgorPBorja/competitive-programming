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
#define print(msg, v) debug << msg; for(auto it = v.begin(); it != v.end(); it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
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

/*
he can put at most sqrt(n) boats

dp[i][j] = cost to put i boats into prefix [0..j]

use range pre-computed sums!

total O(n sqrt(n))
*/

i64 max_boats(i64 n){
    i64 l = 0, r = n, ans = 0;
    while (l <= r){
        const i64 m = l + (r - l) / 2;
        i64 y = (m * (m + 1)) / 2;
        if (y <= n){
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ans;
}

const i64 INF = 2e18;

void solve(){
    i64 n, G;
    cin >> n >> G;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];
    i64 m = max_boats(n);
    // cerr << "max boats m=" << m << endl;

    vector<i64> p(n);
    p[0] = a[0];
    for (i64 i = 1; i < n; i++){
        p[i] = p[i - 1] + a[i];
    }
    
    vector<vector<i64>> dp(m + 1, vector<i64>(n));
    for (i64 i = 0; i < n; i++) dp[0][i] = 0;
    // NOTE m >= 1 always, since 1 * (1 + 1) / 2 = 1 <= n
    for (i64 i = 1; i <= m; i++){  // i-th boat has size i
        dp[i][0] = (i > 1 ? -INF : G - a[0]);
        // boat will be j-i+1=j-(i-1)..j
        for (i64 j = 1; j < n; j++){
            dp[i][j] = dp[i][j - 1];
            if (j - i >= 0 && dp[i - 1][j - i] > -INF){
                dp[i][j] = max(dp[i][j], dp[i - 1][j - i] + G - (p[j] - p[j - i]));
            }
        }
    }
    i64 ans = -INF;
    for (i64 i = 0; i <= m; i++) ans = max(ans, dp[i][n - 1]);
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
