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

namespace Tarjan {
    vector<i64> t_in, lowlink;
    vector<pair<i64, i64>> dfs_tree_edges;

    void dfs(i64 u, const vector<vector<i64>> &g, vector<bool> &vis, i64 &timer, i64 parent = -1){
        vis[u] = true;
        t_in[u] = lowlink[u] = timer++;
        for (i64 v: g[u]){
            if (vis[v] && v != parent){
                // back edge u -> v (except parent)
                lowlink[u] = min(lowlink[u], t_in[v]);
            } else if (!vis[v]){
                dfs_tree_edges.emplace_back(u, v);
                dfs(v, g, vis, timer, u);
                lowlink[u] = min(lowlink[u], lowlink[v]);
            }
        }
    }

    vector<pair<i64, i64>> bridges(const vector<vector<i64>> &g){
        const i64 n = g.size();
        i64 timer = 0;
        vector<bool> vis(n, false);
        t_in = vector<i64>(n);
        lowlink = vector<i64>(n);

        for (i64 u = 0; u < n; u++){
            if (!vis[u]){
                dfs(u, g, vis, timer);
            }
        }
        vector<pair<i64, i64>> bridge_list;
        for (auto[u, to]: dfs_tree_edges){
            if (lowlink[to] > t_in[u]){
                bridge_list.emplace_back(u, to);
            }
        }
        return bridge_list;
    }
}

namespace Toposort {
    i64 c;

    void dfs(i64 u, const vector<vector<i64>> &g, vector<bool> &vis, vector<i64> &order){
        vis[u] = true;
        for (i64 v: g[u]){
            if (!vis[v]){
                dfs(v, g, vis, order);
            }
        }
        order[u] = c;
        --c;
    }

    vector<i64> order(const vector<vector<i64>> &g){
        const i64 n = g.size();
        c = n - 1;
        vector<bool> vis(n, false);
        vector<i64> vertex_order(n);
        for (i64 u = 0; u < n; u++){
            if (!vis[u]) dfs(u, g, vis, vertex_order);
        }
        return vertex_order;
    }
}

void solve(){
    i64 n, m;
    cin >> n >> m;

    vector<vector<i64>> g(n);
    vector<pair<i64, i64>> edges(m);
    for (i64 i = 0; i < m; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
        edges[i] = {a, b};
    }

    vector<pair<i64, i64>> bridges = Tarjan::bridges(g);
    if (bridges.size() > 0){
        cout << 0 << endl;
    } else {  // only put the tree edges in the correct order, everything else as back-edge ("back" according to toposort)
        vector<pair<i64, i64>> dfs_tree_edges = Tarjan::dfs_tree_edges;
        vector<vector<i64>> dag(n);
        for (auto[u, v]: dfs_tree_edges){
            dag[u].emplace_back(v);
        }
        vector<i64> order = Toposort::order(dag);

        sort(dfs_tree_edges.begin(), dfs_tree_edges.end());
        auto find_in_tree = [&dfs_tree_edges](pair<i64, i64> p){
            auto it = lower_bound(dfs_tree_edges.begin(), dfs_tree_edges.end(), p);
            return (it != dfs_tree_edges.end() && *it == p);
        };

        for (i64 i = 0; i < m; i++){
            if (find_in_tree(edges[i])){
                cout << edges[i].first + 1 << " " << edges[i].second + 1 << endl;
            } else if (find_in_tree(make_pair(edges[i].second, edges[i].first))) {
                cout << edges[i].second + 1 << " " << edges[i].first + 1 << endl;
            } else {
                if (order[edges[i].first] > order[edges[i].second]){
                    cout << edges[i].first + 1 << " " << edges[i].second + 1 << endl;
                } else {
                    cout << edges[i].second + 1 << " " << edges[i].first + 1 << endl;
                }
            }
        }
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
