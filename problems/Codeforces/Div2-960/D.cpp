// UNSOLVED

#define TESTCASES
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
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(n), dp(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    dp[0] = 1;  // color whole row
    // can color (0..1, ceil(min(a[0], a[1]) / 2) + (b)) as 
    if (n > 1){
        i64 twopaint = (max(a[0], a[1]) + 1) / 2;
        dp[1] = min((i64)2, twopaint);
        for (i64 i = 2; i < n; i++){
            dp[i] = 1 + dp[i - 1];
            i64 twopaint = (max(a[i - 1], a[i]) + 1) / 2;
            dp[i] = min(dp[i], dp[i - 2] + min(twopaint, (i64)2));
        }
    }
    printmsg("dp=", dp.begin(), dp.end());
    cout << dp[n - 1] << endl;
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
