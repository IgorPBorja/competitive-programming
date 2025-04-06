#define TESTCASES
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

const i64 MOD = 998244353;
i64 dp[(i64)3e5 + 10];
i64 level[(i64)3e5 + 10];

// has to be a BFS dp since we need level-wise information
i64 bfs(const vector<vector<i64>>& adj){
    const i64 root = 0;
    fill(level, level + adj.size(), 0);
    vector<pair<i64, i64>> vertices;  // in bfs order, (u, d)
    vertices.emplace_back(root, 0);
    i64 i = 0;
    i64 max_depth = 0;
    while (i < vertices.size()){
        // process vertex i
        auto[u, d] = vertices[i];
        for (i64 v: adj[u]){
            vertices.emplace_back(v, d + 1);
            max_depth = max(max_depth, d + 1);
        }
        ++i;
        // cout << "i=" << i << " vertices.size()=" << vertices.size() << endl;
    }
    // now do it in reverse BFS order
    reverse(vertices.begin(), vertices.end());
    for (auto[u, d]: vertices){
        if (d == max_depth){
            dp[u] = 1;
            level[max_depth] = (level[max_depth] + 1) % MOD;
        } else {
            dp[u] = (1 + level[d + 1]) % MOD;  // 1 for singleton run
            // exclude neighbors of non-root vertex
            if (d > 0){
                for (i64 v: adj[u]){
                    dp[u] = (dp[u] + MOD - dp[v]) % MOD;
                }
            }
            level[d] = (level[d] + dp[u]) % MOD;
        }
    }
    // printmsg("dp=", dp, dp + adj.size());
    return dp[root];
}

void solve(){
    i64 n;
    cin >> n;
    vector<vector<i64>> adj(n);
    for (i64 i = 1; i < n; i++){
        i64 p;
        cin >> p;
        --p;
        adj[p].emplace_back(i);
    }
    cout << bfs(adj) << endl;
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
