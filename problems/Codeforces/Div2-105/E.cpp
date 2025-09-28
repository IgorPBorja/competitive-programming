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

const i64 INF = (i64)2e18;

void solve(){
    // dp[i][j] = using up to row i and j shrieks
    // Let S = max(s[i]) <= 100
    // complexity: should be O(mn * S) ~ 1e8

    // we need to know least subarray of size k
    // for every k=0..s[i] for every row i
    // For every k complexity is O(s[i] - k)
    // ==> sum(i)sum(k=0..s[i])(s[i]-k) = sum(i)(s[i] * (s[i] + 1)) / 2) ==> O(nS^2) ~ 1e8

    i64 n, m;
    cin >> n >> m;
    vector<i64> s(n), full_sum(n);
    vector<vector<i64>>
        dp(n, vector<i64>(m + 1)),
        a(n),
        pref(n),
        suf(n),
        min_subarray(n);
    for (i64 i = 0; i < n; i++){
        cin >> s[i];
        a[i].resize(s[i]);
        pref[i].resize(s[i] + 1);
        suf[i].resize(s[i] + 1);
        pref[i][0] = 0;
        for (i64 j = 0; j < s[i]; j++){
            cin >> a[i][j];
            pref[i][j + 1] = pref[i][j] + a[i][j];
        }
        suf[i][s[i]] = 0;
        full_sum[i] = pref[i][s[i]];
        for (i64 j = s[i] - 1; j >= 0; j--) suf[i][j] = suf[i][j + 1] + a[i][j];
    }

    for (i64 i = 0; i < n; i++){
        min_subarray[i].assign(s[i] + 1, INF);
        for (i64 k = 0; k <= s[i]; k++){
            for (i64 j = 0; j + k <= s[i]; j++){
                min_subarray[i][k] = min(min_subarray[i][k], full_sum[i] - pref[i][j] - suf[i][j + k]);
            }
        }
    }
    // printgraph("min_subarray=", min_subarray);

    for (i64 x = 0; x <= m; x++){
        // consuming x ==> s[0]-x remaining from middle
        dp[0][x] = (x <= s[0] ? full_sum[0] - min_subarray[0][s[0] - x] : -INF);
    }
    for (i64 i = 1; i < n; i++){
        for (i64 x = 0; x <= m; x++){
            dp[i][x] = -INF;
            for (i64 dx = 0; dx <= min(s[i], x); dx++){  // take dx from row i
                if (dp[i - 1][x - dx] != -INF){
                    // s[i] - dx remain on row i
                    // best is full_sum - min middle subarray of size s[i] - dx
                    dp[i][x] = max(dp[i][x], dp[i - 1][x - dx] + (full_sum[i] - min_subarray[i][s[i] - dx]));
                }
            }
        }
    }
    // printgraph("dp=", dp);
    cout << dp[n - 1][m] << endl;
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
