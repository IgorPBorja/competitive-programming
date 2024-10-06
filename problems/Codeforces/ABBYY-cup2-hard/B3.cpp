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

struct MinSeg {
    vector<i64> seg;
    vector<i64> a;

    MinSeg () {};

    MinSeg (const vector<i64> a) : a(a) {
        const i64 n = a.size();
        seg.resize(4 * n);
        build(0, n - 1, 0);
    }

    i64 query(i64 l, i64 r){
        const i64 n = a.size();
        return query(l, r, 0, n - 1, 0);
    }

    i64 argmin_query(i64 l, i64 r){
        const i64 n = a.size();
        return argmin_query(l, r, 0, n - 1, 0);
    }


private:
    void build(i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = a[l];
        } else {
            i64 m = l + (r - l) / 2;
            build(l, m, 2 * node + 1);
            build(m + 1, r, 2 * node + 2);
            seg[node] = min(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    i64 query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr){
            return seg[node];
        } else if (r <= tm){
            return query(l, r, tl, tm, 2 * node + 1);
        } else if (l > tm){
            return query(l, r, tm + 1, tr, 2 * node + 2);
        } else {
            return min(query(l, tm, tl, tm, 2 * node + 1), query(tm + 1, r, tm + 1, tr, 2 * node + 2));
        }
    }

    i64 argmin_query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr){
            return seg[node];
        } else if (r <= tm){
            return argmin_query(l, r, tl, tm, 2 * node + 1);
        } else if (l > tm){
            return argmin_query(l, r, tm + 1, tr, 2 * node + 2);
        } else {
            i64 left = argmin_query(l, tm, tl, tm, 2 * node + 1);
            i64 right = argmin_query(tm + 1, r, tm + 1, tr, 2 * node + 2);
            return (a[left] < a[right]) ? left : right;
        }
    }
};

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
        for (auto[v, to]: dfs_tree_edges){
            if (lowlink[to] > t_in[v]){
                h[v].emplace_back(to, 1);
            } else {
                h[v].emplace_back(to, 0);
            }
        }
        // printgraph("h=", h);
        return h;
    }
}

struct LCA {
    static constexpr i64 root = 0;
    const vector<vector<pair<i64, i64>>> tree;

    LCA(const vector<vector<pair<i64, i64>>> tree) : tree(tree) {
        t_in.resize(tree.size());
        t_last.resize(tree.size());
        euler_tour();
        blift();

        s = MinSeg(node_heights);
    }

    i64 up(i64 u, i64 delta_h){
        i64 ilog = 30;
        i64 ans = 0;
        while (delta_h > 0){
            while ((1ll << ilog) > delta_h){
                --ilog;
            }
            ans += bridges_up[ilog][u];
            u = parent[ilog][u];
            delta_h -= 1ll << ilog;
        }
        return ans;
    }

    i64 query(i64 u, i64 v){
        i64 lca_height = s.query(min(t_in[u], t_in[v]), max(t_in[u], t_in[v]));
        return up(u, node_heights[t_in[u]] - lca_height) + up(v, node_heights[t_in[v]] - lca_height);
    }
private:
    vector<i64> bridges_visited, nodes_visited, node_heights;
    vector<i64> t_in, t_last;
    vector<vector<i64>> bridges_up, parent;
    MinSeg s;

    // perform euler tour on directed tree
    void euler_tour(i64 u = root, i64 h = 0){
        t_in[u] = nodes_visited.size();
        t_last[u] = nodes_visited.size();
        nodes_visited.emplace_back(u);
        node_heights.emplace_back(h);
        for (auto[v, is_bridge]: tree[u]){
            bridges_visited.emplace_back(is_bridge);
            euler_tour(v, h + 1);
            nodes_visited.emplace_back(u);
            node_heights.emplace_back(h);
            bridges_visited.emplace_back(is_bridge);
            t_last[u] = nodes_visited.size();
        }
    }

    void blift(){
        const i64 n = tree.size();
        i64 ilog = 0;
        while ((1ll << (ilog + 1)) <= n) ++ilog;
        bridges_up = vector<vector<i64>>(ilog + 1, vector<i64>(n, 0));
        parent = vector<vector<i64>>(ilog + 1, vector<i64>(n));
        parent[0][0] = 0;
        for (i64 i = 1; i < n; i++){
            parent[0][i] = nodes_visited[t_in[i] - 1];
        }
        for (i64 u = 0; u < n; u++){
            for (auto[v, is_bridge]: tree[u]){
                bridges_up[0][v] = is_bridge;
            }
        }
        for (i64 k = 1; k <= ilog; k++){
            for (i64 i = 0; i < n; i++){
                parent[k][i] = parent[k - 1][parent[k - 1][i]];
                bridges_up[k][i] = bridges_up[k - 1][i] + bridges_up[k - 1][parent[k - 1][i]];
            }
        }
    }
};

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
    LCA lca_solver(h);

    i64 k;
    cin >> k;
    for (i64 i = 0; i < k; i++){
        i64 s, l;
        cin >> s >> l;
        --s; --l;
        cout << lca_solver.query(s, l) << endl;
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
