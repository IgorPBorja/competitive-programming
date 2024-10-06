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

const i64 MOD = 998244353;

void solve(){
    map<i64, i64> m;
    i64 n, k;
    cin >> n >> k;
    i64 a[n], b[n], dp[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    b[0] = a[0];
    for (i64 i = 1; i < n; i++){
        b[i] = b[i - 1] + a[i];
    }

    dp[0] = (a[0] != k) ? 1 : 0;
    m[b[0]] = (m[b[0]] + dp[0]) % MOD;
    i64 s = dp[0];
    for (i64 i = 1; i < n; i++){
        // discard all j s.t b[j] = b[i] - k
        dp[i] = (s + MOD - m[b[i] - k] + ((b[i] != k) ? 1 : 0)) % MOD;
        s = (s + dp[i]) % MOD;
        m[b[i]] = (m[b[i]] + dp[i]) % MOD;
    }
    // printmsg("a=", a, a + n);
    // printmsg("b=", b, b + n);
    // printmsg("dp=", dp, dp + n);
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
