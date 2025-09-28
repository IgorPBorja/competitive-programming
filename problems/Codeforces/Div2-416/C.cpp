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

constexpr i64 MAXV = 5000;
const i64 INF = (i64)2e18;

void solve(){
    i64 n;
    cin >> n;
    vector<i64> minpos(MAXV + 1, +INF), maxpos(MAXV + 1, -INF);

    vector<i64> a(n), dp(n);
    for (i64 i = 0; i < n; i++) {
        cin >> a[i];
        minpos[a[i]] = min(minpos[a[i]], i);
        maxpos[a[i]] = max(maxpos[a[i]], i);
    }
	// can always not take a[0], so ans is >= 0
    dp[0] = ((minpos[a[0]] == 0 && maxpos[a[0]] == 0) ? a[0] : 0);
    for (i64 i = 1; i < n; i++){
		// try to select [j..i]
		i64 violations = 0;
		dp[i] = -INF;
		vector<i64> seen(MAXV + 1, false);
		i64 xor_distinct = 0;
		vector<i64> local_minpos(MAXV + 1), local_maxpos(MAXV + 1);
		for (i64 j = i; j >= 0; j--){
			if (!seen[a[j]]) {
				local_maxpos[a[j]] = j;
				local_minpos[a[j]] = j;
				seen[a[j]] = true;
				xor_distinct ^= a[j];
				if (maxpos[a[j]] > j || minpos[a[j]] < j) ++violations;
			} else {
				local_minpos[a[j]] = j;
				if (local_minpos[a[j]] == minpos[a[j]] && local_maxpos[a[j]] == maxpos[a[j]]) {
					--violations;  // got full interval
				}
			}

			// can take [j..i]
			if (violations == 0){
				// valid position
				dp[i] = max(dp[i], xor_distinct + (j > 0 ? dp[j - 1] : 0));
			}
			// can always NOT take [j..i], since dp[j-1] won't take any value also on this range
			// because then it would not be all on the same block
			dp[i] = max(dp[i], (j > 0 ? dp[j - 1] : 0));
		}
    }
	// print("minpos=", minpos);
	// print("maxpos=", maxpos);
	// print("dp=", dp);
	cout << dp[n - 1] << endl;
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
