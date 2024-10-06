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
    i64 n, l, r;
    cin >> n >> l >> r;

    // dp[i] = max victories taking up to i - 1
    i64 a[n], dp[n + 1], pref[n + 1];
    pref[0] = 0;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }

    // pl: last index such that a[pl] + ... + a[i] >= l
    // pr: first index such that a[pr] + ... + a[i] <= r
    // as DP in non-decreasing max value on the segment is the last one (greedy approach: take the smallest)
    // we just maintain both to check the segment is valid

    // consider a sentinel value at +INF sitting at a[0]
    dp[0] = 0;
    i64 pl = -1, pr = 0;
    for (i64 i = 0; i < n; i++){
        // must grow pr (delete a[pr])
        while (pref[i + 1] - pref[pr] > r){
            ++pr;
        }
        // can grow pl (delete a[pl])
        while (pl + 1 <= i && pref[i + 1] - pref[pl + 1] >= l){
            ++pl;
        }
        if (pr <= pl){
            dp[i + 1] = max(dp[pl] + 1, dp[i]);
        } else {
            dp[i + 1] = dp[i];
        }
    }
    cout << dp[n] << endl;
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
