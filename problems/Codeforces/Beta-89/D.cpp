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

constexpr i64 MAXN = 100;
// zeroed by default, because global
i64 dp[2][2 * MAXN + 1][MAXN + 1][MAXN + 1];
const i64 MOD = (i64)1e8;

void solve(){
    /*
    dp[b][k][x1][x2] = number of distribution of k blocks with the last block being (horsemen if b else footmen)
        using exactly x1 footmen and x2 horsemen

    Transition is O(max(k1, k2))
    We must have k <= n1 + n2 because on the worst case all blocks have size 1
    Complexity is therefore ~ 2 * (n1 + n2) * n1 * n2 * max(k1, k2) = 2 * 200 * 100 * 100 * 10 = 4 * 10^7
    For 2 seconds should be fine
    */
    i64 n[2], k[2];
    cin >> n[0] >> n[1];
    cin >> k[0] >> k[1];
    for (i64 type: {0, 1}){
        for (i64 i = 1; i <= min(k[type], n[type]); i++){
            if (type == 0) dp[type][1][i][0] = 1;
            else dp[type][1][0][i] = 1;
        }
    }
    for (i64 blocks = 2; blocks <= n[0] + n[1]; blocks++){
        for (i64 x0 = 0; x0 <= n[0]; x0++){
            for (i64 x1 = 0; x1 <= n[1]; x1++){
                // type 0
                for (i64 dx0 = 1; dx0 <= min(k[0], x0); dx0++){
                    dp[0][blocks][x0][x1] = (dp[0][blocks][x0][x1] + dp[1][blocks - 1][x0 - dx0][x1]) % MOD;
                }
                // type 1
                for (i64 dx1 = 1; dx1 <= min(k[1], x1); dx1++){
                    dp[1][blocks][x0][x1] = (dp[1][blocks][x0][x1] + dp[0][blocks - 1][x0][x1 - dx1]) % MOD;
                }
            }
        }
    }
    i64 ans = 0;
    for (i64 blocks = 1; blocks <= n[0] + n[1]; blocks++){
        ans = (ans + dp[0][blocks][n[0]][n[1]] + dp[1][blocks][n[0]][n[1]]) % MOD;
    }
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
