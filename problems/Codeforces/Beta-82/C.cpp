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

void solve(){
    i64 n, m, c0, d0;
    cin >> n >> m >> c0 >> d0;
    
    vector<i64> a(m + 1), b(m + 1), c(m + 1), d(m + 1);
    for (i64 i = 1; i <= m; i++) cin >> a[i] >> b[i] >> c[i] >> d[i];

    vector<vector<i64>> dp(m + 1, vector<i64>(n + 1));
    for (i64 x = 0; x <= n; x++){
        dp[0][x] = (x / c0) * d0;
    }
    for (i64 i = 1; i <= m; i++){
        for (i64 x = 0; x <= n; x++){
            dp[i][x] = 0;
            // try to use q units of type i
            for (i64 q = 0; q * c[i] <= x && q * b[i] <= a[i]; q++){
                dp[i][x] = max(dp[i][x], q * d[i] + dp[i - 1][x - q * c[i]]);
            }
        }
    }
    cout << dp[m][n] << endl;
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
