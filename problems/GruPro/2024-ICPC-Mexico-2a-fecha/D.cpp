// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
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

constexpr i64 N = 800;
// will start with zeroes
i64 dp[18 * N][N];
const i64 MOD = (i64)1e9 + 7;

void solve(){
    // 1-digit matches
    // normalization factor for negative:
    i64 NORM = 9 * N;
    for (i64 d = 1; d <= 9; d++){
        for (i64 e = d + 1; e <= 9; e++){
            ++dp[e - d + NORM][0];
            ++dp[d - e + NORM][0];
        }
    }
    for (i64 i = 1; i < N; i++){
        // worst case is 999999..9 and 10...0
        for (i64 delta = -9 * i + 1; delta <= 9*i - 1; delta++){
            for (i64 d = 0; d <= 9; d++){
                for (i64 e = d + 1; e <= 9; e++){
                    dp[delta + e - d + NORM][i] = (dp[delta + e - d + NORM][i] + dp[delta + NORM][i - 1]) % MOD;
                    dp[delta + d - e + NORM][i] = (dp[delta + d - e + NORM][i] + dp[delta + NORM][i - 1]) % MOD;
                }
            }
        }
    }
    i64 q;
    cin >> q;
    for (i64 _ = 0; _ < q; _++){
        i64 n;
        cin >> n;
        cout << dp[NORM][n - 1] << endl;
    }
}
 
signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--){
		solve();
	}
}
