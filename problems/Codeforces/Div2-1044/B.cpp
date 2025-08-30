#define TESTCASES
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
    i64 n;
    cin >> n;
    vector<i64> g(n);

    for (i64 i = 0; i < n; i++){
        cin >> g[i];
    }

    sort(all(g));
    // greedy: pair max with 2nd max, ans so on
    // it is the minimum value of sum max(g[i1], g[i2])
    // over all pairings
    reverse(all(g));
    i64 ans = 0;
    while (g.size() > 1){
        const i64 k = g.size();
        vector<i64> new_g;
        for (i64 i = 0; i < k; i += 2){
            if (i + 1 < k){
                // only min representative
                new_g.emplace_back(0);
                ans += max(g[i], g[i + 1]);
            } else {
                new_g.emplace_back(g[i]);
            }
        }
        g = new_g;
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
