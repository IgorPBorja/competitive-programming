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

void solve(){
    // each mask of popcount = k appears once at level k
    i64 n, m, k;
    cin >> n >> m >> k;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];
    vector<vector<i64>> M(n, vector<i64>(n));
    for (i64 i = 0; i < k; i++){
        i64 u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        M[u][v] = w;
    }

    // complexity: O(n^2 * 2^n)
    // dp[i][msk] = max value for msk ending at i
    vector<vector<i64>> dp(n, vector<i64>(1ll << n, 0));
    vector<i64> bitmasks(1ll << n);
    iota(all(bitmasks), 0);
    sort(all(bitmasks), [](i64 x, i64 y){
        return (__builtin_popcount(x) < __builtin_popcount(y))
        || (__builtin_popcount(x) == __builtin_popcount(y) && x < y);
    });
    for (i64 i = 0; i < n; i++){
        dp[i][1ll << i] = a[i];  // 2^i
    }
    for (i64 i = n + 1; i < (1ll << n); i++){
        i64 msk = bitmasks[i];
        i64 b = __builtin_popcount(msk);
        if (b > m) break;
        // get first active bit (msb)
        for (i64 j = 0; j < n; j++){
            if (msk & (1ll << j)){
                for (i64 k = 0; k < n; k++){
                    if ((msk & (1ll << k)) && k != j){
                        dp[j][msk] = max(dp[j][msk], dp[k][msk ^ (1ll << j)] + a[j] + M[k][j]);
                    }
                }
            }
        }
    }
    i64 ans = 0;
    for (i64 msk: bitmasks){
        if (__builtin_popcount(msk) == m){
            for (i64 j = 0; j < n; j++){
                if (msk & (1ll << j)){
                    ans = max(ans, dp[j][msk]);
                }
            }
        }
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
