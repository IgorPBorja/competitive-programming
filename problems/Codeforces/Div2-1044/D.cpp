#define TESTCASES
#define debug cout

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'

#define eb emplace_back
#define ep emplace
 
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

/*
Either solves prefix 0..i-1 then i takes 1 of fall damage
and ends up alone

Or at some stack j..i remove i-1 entirely. Note that for every j
the same pile with i-1 and i will be formed, so in this early removal
flow is it **always better for j=0**, i.e to remove i-1 at the first move
Which amounts to a[i-1] + a[i] - i moves, then solving prefix i-2
*/

void solve(){
    i64 n;
    cin >> n;
    vector<i64> h(n), dp(n);
    for (i64 i = 0; i < n; i++){
        cin >> h[i];   
    }
    dp[0] = h[0];
    dp[1] = h[0] + h[1] - 1;
    for (i64 i = 2; i < n; i++){
        dp[i] = min(
            dp[i - 1] + h[i] - 1,
            dp[i - 2] + h[i - 1] + max(h[i] - i, (i64)0)
        );
    }
    cout << dp[n - 1] << endl;
    
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
