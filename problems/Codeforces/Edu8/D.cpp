// #define TESTCASES
 
#include <bits/stdc++.h>
using namespace std;
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

const i64 MOD = (i64)1e9 + 7;
// FIXME to 2000
const i64 MAX_M = 5, MAX_LEN = 5;
// dp[i][j][k] = number of integers of length i and remainder j mod m that are d-magic
// and are strictly under (if k) or matching limiting value X

i64 f(const string& s, i64 m, i64 d, bool exclusive){
    const i64 n = s.size();
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++) a[i] = s[i] - '0';
    i64 dp[n + 1][m][2];
    memset(dp, 0, sizeof(dp));
    
    ++dp[0][0][1] = 1;
    for (i64 i = 1; i <= n; i++){
        for (i64 r = 0; r < m; r++){
            if (i % 2 == 0){
                // can only be d
                dp[i][(10 * r + d) % m][0] += dp[i - 1][r][0];
                if (d == a[i - 1]){
                    dp[i][(10 * r + d) % m][1] += dp[i - 1][r][1];
                } else if (d < a[i - 1]){
                    dp[i][(10 * r + d) % m][0] += dp[i - 1][r][1];
                }
                continue;
            }
            // first try the ones that match fully the prefix
            for (i64 c = 0; c <= a[i - 1]; c++){
                if (i % 2 == 1 && c == d) continue;
                dp[i][(10 * r + c) % m][(c == a[i - 1])] = (
                    dp[i][(10 * r + c) % m][(c == a[i - 1])] + dp[i - 1][r][1]
                ) % MOD;
            }
            // then try the ones that already don't match
            for (i64 c = 0; c < 10; c++){
                if (i % 2 == 1 && c == d) continue;
                dp[i][(10 * r + c) % m][0] = (
                    dp[i][(10 * r + c) % m][0] + dp[i - 1][r][0]
                ) % MOD;
            }
        }
    }
    i64 ans = 0;
    ans = dp[n][0][0];
    if (!exclusive) ans = (ans + dp[n][0][1]) % MOD;
    return ans;
}

void solve(){
    i64 m, d;
    string a, b;
    
    cin >> m >> d;
    cin >> a >> b;
    i64 ans = (f(b, m, d, false) + MOD - f(a, m, d, true)) % MOD;
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
