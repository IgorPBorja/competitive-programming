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
    // dp[x] = current largest subsequence ending at x
    map<i64, i64> dp;
    i64 n;
    cin >> n;
    vector<i64> a(n);
    i64 ans = 0;
    map<i64, i64> prev, cur;
    i64 last = 0;
    // we have at most 2N keys: a[i] and a[i] - 1 for all i
    for (i64 i = 0; i < n; i++){
        i64 x;
        cin >> x;
        a[i] = x;
        if (dp[x] >= dp[x - 1] + 1){
            // keep it
        } else { // if (dp[x - 1] + 1 > dp[x]){
            cur[x] = i + 1;
            prev[x] = cur[x - 1];   // defaults to 0 if does not exist
            dp[x] = dp[x - 1] + 1;
        }
        if (dp[x] > ans){
            last = cur[x];
            ans = dp[x];
        }
    }
    cout << ans << endl;
    // do greedy algorithm now that we have last position
    vector<i64> idxs;
    i64 target = a[last - 1];
    for (i64 i = last - 1; i >= 0; i--){
        if (a[i] == target){
            idxs.emplace_back(i + 1);  // 1-indexed
            --target;
        }
    }
    reverse(all(idxs));
    for (i64 i: idxs) cout << i << " ";
    cout << endl;
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
