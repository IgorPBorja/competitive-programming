// #define TESTCASES
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
    i64 timer;

    void dfs(i64 u, const vector<vector<i64>> &g, vector<bool> &vis, i64 parent = -1){
        vis[u] = true;
        t_in[u] = lowlink[u] = timer++;
        for (i64 to: g[u]){
            if (to == parent) continue;
            else if (vis[to]){
                // back edge on DFS tree
                lowlink[u] = min(t_in[to], lowlink[u]);
            } else {
                dfs(to, g, vis, u);
                dfs_tree_edges.emplace_back(u, to);
                lowlink[u] = min(lowlink[to], lowlink[u]);
            }
        }
    }

    // lowlink(u) = min(t_in(u), min_{p->u}t_in(u), min_{u->to em tree}lowlink(to))
    vector<vector<pair<i64, i64>>> dfs_tree_bridges(const vector<vector<i64>> &g) {
        const i64 n = g.size();
        vector<bool> vis(n, false);
        lowlink = vector<i64>(n, INF);
        t_in = vector<i64>(n, INF);
        dfs_tree_edges.clear();
        timer = 0;

        for (i64 u = 0; u < n; u++){
            if (!vis[u]){
                dfs(u, g, vis);
            }
        }

        vector<vector<pair<i64, i64>>> h(n);
        for (i64 u = 0; u < n; u++){
            for (i64 v: g[u]){
                h[u].emplace_back(v, 0);
            }
            sort(h[u].begin(), h[u].end());
        }
        for (auto[v, to]: dfs_tree_edges){
            if (lowlink[to] > t_in[v]){
                // v -> to bridge
                // and also to -> v
                auto it = lower_bound(h[v].begin(), h[v].end(), make_pair(to, (i64)0));
                ++it->second;
                it = lower_bound(h[to].begin(), h[to].end(), make_pair(v, (i64)0));
                ++it->second;
            }
        }
        // printgraph("h=", h);
        return h;
    }
}

void dfs(i64 u, const vector<vector<pair<i64, i64>>> &g, vector<bool> &vis, vector<i64> &bridge_count, i64 c = 0){
    vis[u] = true;
    bridge_count[u] = c;
    for (auto[v, is_bridge]: g[u]){
        if (!vis[v]){
            dfs(v, g, vis, bridge_count, c + is_bridge);
        }
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

    vector<vector<pair<i64, i64>>> h = Tarjan::dfs_tree_bridges(g);

    i64 k;
    cin >> k;
    for (i64 i = 0; i < k; i++){
        i64 s, l;
        cin >> s >> l;
        --s; --l;
        vector<bool> vis(n, false);
        vector<i64> bridge_count(n, 0);
        dfs(s, h, vis, bridge_count);
        cout << bridge_count[l] << endl;
    }
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
