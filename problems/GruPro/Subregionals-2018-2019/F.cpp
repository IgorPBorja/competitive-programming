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
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << setw(3) << (v != INF ? to_string(v) : "INF") << " "; \
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

constexpr i64 M = 1000;
constexpr i64 T = 86400;
constexpr i64 N = 10;
constexpr i64 INF = (i64)2e18;

// dp[msk][t] = max value using EXACTLY stages on msk (at least once each), on interval [0,t]
i64 dp[(1ll << N)][T + 1];

void solve(){
    // stage idx, start time, value
    vector<tuple<i64, i64, i64>> end_at[T + 1];

    i64 n;
    cin >> n;
    for (i64 i = 0; i < n; i++){
        i64 m_i;
        cin >> m_i;
        for (i64 j = 0; j < m_i; j++){
            i64 t0, tf, v;
            cin >> t0 >> tf >> v;
            end_at[tf].emplace_back(i, t0, v);
        }
    }

    for (i64 msk = 0; msk < (1ll << n); msk++){
        for (i64 t = 0; t <= T; t++){
            dp[msk][t] = ((t == 0) ? 0 : dp[msk][t - 1]);
            if (t == 0){
                dp[msk][t] = (msk == 0 ? 0 : -INF);
            } else {
                dp[msk][t] = dp[msk][t - 1];
            }
            for (auto[stage, t0, v]: end_at[t]){
                if (msk & (1ll << stage)){
                    if (dp[msk][t0] != -INF){
                        dp[msk][t] = max(dp[msk][t], v + dp[msk][t0]);
                    }
                    if (dp[msk ^ (1ll << stage)][t0] != -INF){
                        dp[msk][t] = max(dp[msk][t], v + dp[msk ^ (1ll << stage)][t0]);
                    }
                }
            }
        }
    }

    if (dp[(1ll << n) - 1][T] != -INF){
        cout << dp[(1ll << n) - 1][T] << endl;
    } else {
        cout << -1 << endl;
    }
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
