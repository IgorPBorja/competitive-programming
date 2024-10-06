#define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
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

const i64 INF = 1e18;

namespace Tarjan {
    vector<i64> lowlink, t_in;
    vector<pair<i64, i64>> dfs_tree_edges;
    vector<i64> subtree;
    i64 timer;

    void dfs(i64 u, const vector<vector<i64>> &g, vector<bool> &vis, i64 parent = -1){
        vis[u] = true;
        t_in[u] = lowlink[u] = timer++;
        ++subtree[u];
        for (i64 to: g[u]){
            if (to == parent) continue;
            else if (vis[to]){
                // back edge on DFS tree
                lowlink[u] = min(t_in[to], lowlink[u]);
            } else {
                dfs(to, g, vis, u);
                subtree[u] += subtree[to];
                dfs_tree_edges.emplace_back(u, to);
                lowlink[u] = min(lowlink[to], lowlink[u]);
            }
        }
    }

    // lowlink(u) = min(t_in(u), min_{p->u}t_in(u), min_{u->to em tree}lowlink(to))
    pair<vector<pair<i64, i64>>, vector<i64>> dfs_tree_bridges(const vector<vector<i64>> &g) {
        const i64 n = g.size();
        vector<bool> vis(n, false);
        lowlink = vector<i64>(n, INF);
        t_in = vector<i64>(n, INF);
        subtree = vector<i64>(n, 0);
        dfs_tree_edges.clear();
        timer = 0;

        for (i64 u = 0; u < n; u++){
            if (!vis[u]){
                dfs(u, g, vis);
            }
        }

        vector<pair<i64, i64>> bridges;
        for (auto[v, to]: dfs_tree_edges){
            if (lowlink[to] > t_in[v]){
                bridges.emplace_back(v, to);
            }
        }
        return { bridges, subtree };
    }
}

void weighted_subtree_size(i64 u, const vector<vector<i64>> &g, const vector<i64> &weights, vector<i64> &dp){
    dp[u] = weights[u];
    for (i64 v: g[u]){
        if (dp[v] == 0){
            weighted_subtree_size(v, g, weights, dp);
        }
        dp[u] += dp[v];
    }
}

void solve(){
    i64 n, m;
    cin >> n >> m;

    vector<vector<i64>> g(n);
    for (i64 i = 0; i < m; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    auto[bridges, subtree_sz] = Tarjan::dfs_tree_bridges(g);
    sort(bridges.begin(), bridges.end());

    // printgraph("bridge_graph=", bridge_graph);
    // printmsg("scc_sizes=", scc_sizes.begin(), scc_sizes.end());
    // printmsg("dp=", dp.begin(), dp.end());

    auto find_bridge_end = [](vector<pair<i64, i64>> &v, pair<i64, i64> x){
        auto it = lower_bound(v.begin(), v.end(), x);
        auto it2 = lower_bound(v.begin(), v.end(), make_pair(x.second, x.first));
        if (it != v.end() && *it == x){
            return it->second;
        } else if (it2 != v.end() && *it2 == make_pair(x.second, x.first)) {
            return it2->second;
        } else {
            return (i64)(-1);
        }
    };
    i64 ans = INF;
    for (i64 u = 0; u < n; u++){
        for (i64 v: g[u]){
            i64 to = find_bridge_end(bridges, make_pair(u, v));
            if (to != -1){
                i64 l = ((n - subtree_sz[to]) * (n - subtree_sz[to] - 1)) / 2;
                i64 r = (subtree_sz[to] * (subtree_sz[to] - 1)) / 2;
                ans = min(ans, l + r);
            } else {
                ans = min(ans, (n * (n - 1)) / 2);
            }
        }
    }
    cout << ans << endl;
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
