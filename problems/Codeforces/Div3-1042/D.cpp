#define TESTCASES
#define debug cout

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'

#define eb emplace_back
#define ep emplace
 
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
    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 u , v;
        cin >> u >> v;
        --u; --v;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    i64 leaves = 0;
    for (i64 u = 0; u < n; u++){
        leaves += (adj[u].size() == 1);
    }
    
    // fixing the final root,
    // each operation removes a non-shallow leaf (in optimal sequence)
    // and makes root not a leaf (if it was a leaf)
    i64 ans = leaves;
    for (i64 root = 0; root < n; root++){
        i64 shallow_leaves = 0;
        for (i64 v: adj[root]){
            if (adj[v].size() == 1) ++shallow_leaves;
        }
        ans = min(ans, leaves - shallow_leaves - (adj[root].size() == 1));
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

