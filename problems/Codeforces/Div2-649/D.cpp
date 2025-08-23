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

// dfs tree w/ depth and parent
void dfsd(
    const vector<vector<i64>>& adj,
    i64 u,
    vector<i64>& depth,
    vector<i64>& parent,
    i64 p = -1,
    i64 d = 0
){
    depth[u] = d;
    parent[u] = p;
    for (i64 v: adj[u]){
        if (depth[v] == -1){
            dfsd(adj, v, depth, parent, u, d + 1);
        }
    }
}

vector<i64> build_cycle(i64 up, i64 down, vector<i64>& parent){
    vector<i64> path;
    i64 cur = down;
    while (cur != parent[up]){
        path.emplace_back(cur);
        cur = parent[cur];
    }
    return path;
}

// go from root,
// and get either all with depth odd or all from depth even
// in BFS-order, until iset (independent set) is filled.
// We know that going in BFS order we can't add two elements u,v
// to the iset with |d(u)-d(v)| >= k (and d(v) > d(u) WLOG)
// since then we would have v, p^2(v), ..., w=p^{ceil(k/2)-1} and then u above
// which is more than max size of ceil(k/2)
// Therefore depth diff is < k and there is no back-edge, which guarantees set is independent.
vector<i64> build_independent_set(
    i64 root,
    const vector<vector<i64>>& adj,
    const vector<i64>& depth,
    i64 k
){
    vector<i64> independent_set[2];
    const i64 max_size = (k + 1) / 2;
    // bfs
    queue<i64> q;
    q.emplace(root);
    vector<i64> vis(adj.size(), false);
    while (!q.empty()){
        i64 u = q.front();
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        // this depth check is just to avoid the iset 1 filling first
        // but then we add someone invalid to iset 0 (i.e someone that has a back-edge)
        // and return iset 0 instead of 1
        if (depth[u] <= k - 1 && independent_set[depth[u] % 2].size() < max_size){
            independent_set[depth[u] % 2].emplace_back(u);
        }
        for (i64 v: adj[u]){
            // depth[v] > depth[u] ensures bfs order happens like it would on the dfs-induced tree
            if (depth[v] > depth[u] && !vis[v]){
                q.emplace(v);
            }
        }
    }
    if (independent_set[0].size() == max_size){
        return independent_set[0];
    } else {
        return independent_set[1];
    }
}

void solve(){
    i64 n, m, k;
    cin >> n >> m >> k;
    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < m; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<i64> parent(n), depth(n, -1);
    dfsd(adj, 0, depth, parent);
    // debug << "dfs ok" << endl;
    // return;

    for (i64 u = 0; u < n; u++){
        for (i64 v: adj[u]){
            if (depth[v] < depth[u] - 1 && depth[u] - depth[v] <= k - 1){
                // cycle of length at most k
                vector<i64> path = build_cycle(v, u, parent);
                cout << 2 << endl;
                cout << path.size() << endl;
                for (i64 x: path){
                    cout << x + 1 << " ";  // 1-indexed
                }
                cout << endl;
                return;
            }
        }
    }

    // there is no backedge on dfs tree: edge uv with |d(u) - d(v)| <= k - 1
    vector<i64> independent_set = build_independent_set(0, adj, depth, k);
    cout << 1 << endl;
    for (i64 x: independent_set){
        cout << x + 1 << " ";  // 1-indexed
    }
    cout << endl;
    return;
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
