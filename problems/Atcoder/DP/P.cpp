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

const i64 MOD = (i64)1e9 + 7;

i64 paint(i64 u, vector<vector<i64>> &adj, vector<array<i64, 2>> &dp, i64 color, i64 parent = -1){
    if (dp[u][color] == 0){
        i64 ans = 1;
        for (i64 v: adj[u]){
            if (v == parent) continue;
            i64 opposite_color = paint(v, adj, dp, 1 - color, u);
            i64 same_color = (color == 0) ? 0 : paint(v, adj, dp, color, u);
            ans = (ans * (opposite_color + same_color)) % MOD;
        }
        dp[u][color] = ans;
    }
    return dp[u][color];
}

void solve(){
    i64 n;
    cin >> n;

    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }

    i64 ans = 1;
    vector<array<i64, 2>> dp(n, {0, 0});
    for (i64 i = 0; i < n; i++){
        if (dp[i][0] == 0 && dp[i][1] == 0){
            // new connected component
            paint(i, adj, dp, 0);
            paint(i, adj, dp, 1);
            ans = (ans * (dp[i][0] + dp[i][1]) % MOD) % MOD;
        }
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
