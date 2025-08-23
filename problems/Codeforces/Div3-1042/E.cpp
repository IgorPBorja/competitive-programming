#define TESTCASES
#define debug cout

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

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(n), b(n), dp(n);
    for (i64 i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (i64 i = 0; i < n; i++) {
        cin >> b[i];
    }
    dp[n - 1] = a[n - 1] == b[n - 1];
    for (i64 i = n - 2; i >= 0; i--){
        dp[i] = dp[i + 1] & ((b[i] == (a[i] ^ a[i + 1])) || (b[i] == (a[i] ^ b[i + 1])) || (b[i] == a[i]));
    }
    // printmsg("dp=", dp.begin(), dp.end());
    cout << (dp[0] ? "YES" : "NO") << endl;
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

