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
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

/*
- Find centroid from arbitrary root
- Reroot on centroid (rebuild graph)
- Make centroid the max value
- Call solve for the other trees

Basically we build the centroid tree

Since each level transition on the centroid tree halves the size, depth is O(log n)
Building each level is O(n) (since the subtrees from the nodes of each level form a partition of the original tree)

Optimization:
Instead of rebuilding adj, which is kind of complex, we mark centroids as removed!
(effectively cutting of edges and splitting the tree)
*/

const i64 INF = (i64)2e18;

namespace CentroidDecomposition {
    i64 subtree_size(i64 u, const vector<vector<i64>>& adj, vector<i64>& s, vector<i64>& blocked, i64 p = -1){
        s[u] = 1;
        for (i64 v: adj[u]){
            if (v == p) continue;
            if (blocked[v]) continue;
            s[u] += subtree_size(v, adj, s, blocked, u);
        }
        return s[u];
    }

    // find centroid of subtree 
    i64 find_centroid(i64 u, const vector<vector<i64>>& adj, vector<i64>& s, vector<i64>& blocked, i64 total_size, i64 p = -1){
        for (i64 v: adj[u]){
            if (v == p) continue;
            if (blocked[v]) continue;
            if (2 * s[v] >= total_size){
                return find_centroid(v, adj, s, blocked, total_size, u); // there can be only one such vertex
            }
        }
        return u;
    }

    // total_size = size of subtree rooted at root (considering deletions)
    // @return centroid subtree root
    i64 _build_centroid_tree(
        const vector<vector<i64>>& adj,
        vector<i64>& blocked,
        vector<vector<i64>>& centroid_adj,
        vector<i64>& sz,
        i64 total_size,
        i64 root = 0
    ){
        subtree_size(root, adj, sz, blocked);
        i64 c = find_centroid(root, adj, sz, blocked, total_size);
        blocked[c] = true;
        for (i64 v: adj[c]){
            if (blocked[v]) continue;
            // build centroid subtree on partition and get its root
            i64 c2 = _build_centroid_tree(adj, blocked, centroid_adj, sz, sz[v], v);
            centroid_adj[c].emplace_back(c2);
        }
        return c;
    }

    // @return pair (centroid tree root, directed centroid tree)
    pair<i64, vector<vector<i64>>> centroid_tree(const vector<vector<i64>>& adj){
        const i64 n = adj.size();
        vector<i64> blocked(n, false), sz(n);
        vector<vector<i64>> centroid_adj(n);
        i64 master_centroid = _build_centroid_tree(
            adj, blocked, centroid_adj, sz, n
        );
        return {master_centroid, centroid_adj};
    }
}

vector<i64> assign(const vector<vector<i64>>& adj, i64 max_value){
    const i64 n = adj.size();
    auto[c, centroid_adj] = CentroidDecomposition::centroid_tree(adj);
    vector<i64> assignment(n);

    // per level
    queue<pair<i64, i64>> q;
    q.emplace(c, 0);
    while (!q.empty()){
        auto[u, lvl] = q.front();
        q.pop();
        assignment[u] = max_value - lvl;
        for (i64 v: centroid_adj[u]){
            q.emplace(v, lvl + 1);
        }
    }
    return assignment;
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
    vector<i64> ans = assign(adj, (i64)26);
    for (i64 i = 0; i < n; i++) {
        // 'A' is top, 'Z' is bottom
        cout << (char)('A' + 26 - ans[i]) << " ";
    }
    cout << endl;
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
