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

const i64 p = 31, q[2] = {(i64)1e9 + 7, (i64)1e9 + 9};
const i64 M = 1e6;
const i64 MOD = (i64)1e9 + 7;
i64 pows[2][M + 1], inv_pows[2][M + 1];
unordered_map<i64, i64> cnt_per_size[M + 1];

i64 bexp(i64 a, i64 e, i64 mod){
    if (e == 0){
        return 1;
    } else {
        const i64 b = bexp(a, e / 2, mod);
        if (e % 2 == 0){
            return (b * b) % mod;
        } else {
            return (a * ((b * b) % mod)) % mod;
        }
    }
}

i64 rollingHash(const string& s){
    i64 cur[2] = {0, 0};
    for (i64 i = 0; i < s.size(); i++){
        cur[0] = (cur[0] + (i64)(s[i] - 'a') * pows[0][i]) % q[0];
        cur[1] = (cur[1] + (i64)(s[i] - 'a') * pows[1][i]) % q[1];
    }
    return cur[0] * q[1] + cur[1];
}

void solve(){
    string s;
    i64 k;
    cin >> s;
    cin >> k;
    for (i64 i = 0; i < k; i++){
        string t;
        cin >> t;
        ++cnt_per_size[t.size()][rollingHash(t)];
    }

    const i64 n = s.size();
    // compute rolling hash
    i64 h[2][n + 1];
    h[0][0] = h[1][0] = 0;
    for (i64 i = 0; i < n; i++){
        h[0][i + 1] = (h[0][i] + (i64)(s[i] - 'a') * pows[0][i]) % q[0];
        h[1][i + 1] = (h[1][i] + (i64)(s[i] - 'a') * pows[1][i]) % q[1];
    }
    i64 dp[n + 1];
    dp[0] = 1;
    for (i64 i = 1; i <= n; i++){
        dp[i] = 0;
        // try to grab a suffix of size j <= i
        for (i64 j = 1; j <= i; j++){
            // last j on h[0...i]
            // ==> remove h[0...i-j] and multiply the remainder by p^-j
            i64 h0 = ((h[0][i] + q[0] - h[0][i - j]) * inv_pows[0][i - j]) % q[0];
            i64 h1 = ((h[1][i] + q[1] - h[1][i - j]) * inv_pows[1][i - j]) % q[1];
            dp[i] = (dp[i] + cnt_per_size[j][h0 * q[1] + h1] * dp[i - j]) % MOD;
        }
    }
    cout << dp[n] << endl;
}
 
signed main(){
    // precompute powers
    pows[0][0] = pows[1][0] = inv_pows[0][0] = inv_pows[1][0] = 1;
    i64 invp[2] = {bexp(p, q[0] - 2, q[0]), bexp(p, q[1] - 2, q[1])};
    for (i64 i = 1; i <= M; i++){
        pows[0][i] = (pows[0][i - 1] * p) % q[0];
        pows[1][i] = (pows[1][i - 1] * p) % q[1];
        inv_pows[0][i] = (inv_pows[0][i - 1] * invp[0]) % q[0];
        inv_pows[1][i] = (inv_pows[1][i - 1] * invp[1]) % q[1];
    }

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
