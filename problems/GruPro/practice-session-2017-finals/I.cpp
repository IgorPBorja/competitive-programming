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

namespace mst {
    struct DSU {
        vector<i64> p, sz; 

        DSU(i64 n){
            p.resize(n);
            iota(all(p), 0);
            sz.assign(n, 1);
        }

        i64 find(i64 x){
            if (p[x] == x) {
                // is root
                return x;
            } else {
                p[x] = find(p[x]);  // compress
                return p[x];
            }
        }

        bool merge(i64 x, i64 y){
            i64 rx = find(x), ry = find(y);
            if (rx == ry){
                return false;
            } else {
                if (sz[rx] > sz[ry]) swap(rx, ry);
                p[rx] = ry;
                sz[ry] += sz[rx];
                return true;
            }
        }
    };

    map<pair<i64, i64>, bool> in_mst;
    i64 cost = 0;
    vector<vector<pair<i64, i64>>> adj;

    void kruskal(vector<tuple<i64, i64, i64>>& edges, i64 n){
        sort(all(edges));
        DSU d(n);
        adj.resize(n);
        for (auto[w, u, v]: edges){
            if (d.find(u) != d.find(v)){
                in_mst[{min(u, v), max(u, v)}] = true;
                cost += w;
                d.merge(u, v);
                adj[u].emplace_back(w, v);
                adj[v].emplace_back(w, u);
            }
        }
    }
}

namespace lca {
    vector<i64> d; 
    vector<vector<i64>> blift, parent_lift;
    vector<i64> parent, weight;

    void _dfs(i64 u, i64 w0 = 0, i64 cur_d = 0, i64 p = 0){
        d[u] = cur_d;
        parent[u] = p;
        weight[u] = w0;
        for (auto[w, v] : mst::adj[u]){
            if (v != p){
                _dfs(v, w, cur_d + 1, u);
            }
        }
    }

    void lift(){
        i64 lg = 1;
        const i64 n = mst::adj.size();
        while ((1ll << (lg + 1) <= n)){
            ++lg;
        }
        d.resize(n);
        parent.resize(n);
        weight.resize(n);
        _dfs(0);

        blift.assign(lg + 1, vector<i64>(n));
        blift[0] = weight;
        parent_lift.assign(lg + 1, vector<i64>(n));
        parent_lift[0] = parent;
        for (i64 i = 1; i <= lg; i++){
            for (i64 u = 0; u < n; u++){
                blift[i][u] = max(blift[i - 1][parent_lift[i - 1][u]], blift[i - 1][u]);
                parent_lift[i][u] = parent_lift[i - 1][parent_lift[i - 1][u]];
            }
        }
    }

    pair<i64, i64> max_up(i64 u, i64 k){
        i64 ans = 0;
        for (i64 i = blift.size() - 1; i >= 0; i--){
            if ((k & (1ll << i))){
                // calculate ans before going up!
                ans = max(ans, blift[i][u]);
                u = parent_lift[i][u];
            }
        }
        return {u, ans};
    }

    i64 max_query(i64 u, i64 v){
        // if (u == v) return 0;
        if (d[u] < d[v]){
            swap(u, v);
        }
        auto[_u, ans] = max_up(u, d[u] - d[v]);
        u = _u;
        if (u == v){
            return ans;
        }
        for (i64 i = blift.size() - 1; i >= 0; i--){
            if (parent_lift[i][u] != parent_lift[i][v]){
                ans = max(ans, max(blift[i][u], blift[i][v]));
                u = parent_lift[i][u];
                v = parent_lift[i][v];
            }
        }
        // now just step one
        ans = max(ans, max(weight[u], weight[v]));
        return ans;
    }
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<tuple<i64, i64, i64>> edges;
    map<pair<i64, i64>, i64> cost_map;
    i64 w, a, b;
    for (i64 i = 0; i < m; i++){
        cin >> a >> b >> w;
        --a; --b;  // 0-indexing
        edges.emplace_back(w, a, b);
        cost_map[{min(a, b), max(a, b)}] = w;
    }
    mst::kruskal(edges, n);
    lca::lift();

    i64 q;
    cin >> q;
    for (i64 i = 0; i < q; i++){
        cin >> a >> b;
        --a; --b;   // 0-indexing
        if (mst::in_mst[{min(a, b), max(a, b)}]){
            cout << mst::cost << endl;
        } else {
            const i64 query = lca::max_query(a, b);
            cout << mst::cost - query + cost_map[{min(a, b), max(a, b)}] << endl;
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
