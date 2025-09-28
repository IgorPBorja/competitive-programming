#define TESTCASES
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
    string text;
    cin >> text;
    const i64 n = text.size();

    const i64 INF = (i64)2e18;

    vector<vector<i64>> dp(n, vector<i64>(n));
    for (i64 i = 0; i < n; i++) dp[i][i] = 0;
    for (i64 i = 0; i + 1 < n; i++) dp[i][i + 1] = (text[i] != text[i + 1]);
    for (i64 s = 2; s <= n; s++){
        for (i64 i = 0; i + s <= n; i++){
            dp[i][i + s - 1] = INF;
            // replacing
            dp[i][i + s - 1] = min(dp[i][i + s - 1], dp[i + 1][i + s - 2] + (text[i] != text[i + s - 1]));
            // removing last
            dp[i][i + s - 1] = min(dp[i][i + s - 1], dp[i][i + s - 2] + 1);
            // inserting after last
            dp[i][i + s - 1] = min(dp[i][i + s - 1], dp[i + 1][i + s - 1] + 1);
        }
    }
    cout << dp[0][n - 1] << endl;
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
