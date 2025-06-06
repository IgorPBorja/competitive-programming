// #define TESTCASES
// #define DEBUG
 
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

void subtree_sizes(i64 u, const vector<vector<i64>>& adj, vector<i64>& sz, i64 p = -1){
    sz[u] = 1;
    for (i64 v: adj[u]){
        if (v == p) continue;
        subtree_sizes(v, adj, sz, u);
        sz[u] += sz[v];
    }
}

i64 centroid(i64 u, const vector<vector<i64>>& adj, const vector<i64>& sz, i64 p = -1){
    const i64 n = adj.size();
    for (i64 v: adj[u]){
        if (v == p) continue;
        if (sz[v] > n / 2) return centroid(v, adj, sz, u);
    }
    return u;
}

void solve(){
    i64 n;
    cin >> n;
    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    vector<i64> sz(n);
    subtree_sizes(0, adj, sz);
    cout << centroid(0, adj, sz) + 1 << endl;
}
 
signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
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
