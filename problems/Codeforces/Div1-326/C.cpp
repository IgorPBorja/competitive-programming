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
#define i32 int32_t
#define u64 uint64_t
#define i128 __int128

#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;

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

const i64 A = 10;

struct LCA {
    vector<vector<i64>> blift;
    vector<vector<vector<i64>>> lifted_min;
    vector<i64> h, parents;
    const vector<vector<i64>> init;

    LCA(const vector<vector<i64>> &adj, const vector<vector<i64>> &init, const i64 root = 0) : init(init) {
        const i64 n = adj.size();
        h.resize(n);
        parents.resize(n, -1);
        dfs_heights(root, adj, 0);

        build();
    }

    // lca of u and v (where u is at less depth)
    vector<i64> query(i64 u, i64 v){
        if (h[u] > h[v]) swap(u, v);

        // set for the lowest on the tree
        vector<i64> ans = init[u];

        auto[v2, vpath_set] = ascend(v, h[v] - h[u]);
        v = v2;
        ans = merge(ans, vpath_set);
        if (u == v) return ans;

        // go up simultaneous until just below lca
        const i64 ilog = blift.size() - 1;
        for (i64 i = ilog; i >= 0; i--){
            if (blift[i][u] != blift[i][v]){
                ans = merge(merge(ans, lifted_min[i][u]), lifted_min[i][v]);
                u = blift[i][u];
                v = blift[i][v];
            }
        }
        return merge(ans, merge(init[parents[u]], init[parents[v]]));  // include the LCA itself
    }

    pair<i64,vector<i64>> ascend(i64 u, i64 k){
        vector<i64> ans = init[u];
        for (i64 i = 0; i < blift.size(); i++){
            if ((k >> i) & 1){
                ans = merge(ans, lifted_min[i][u]);
                u = blift[i][u];
            }
        }
        return {u, ans};
    }

    void dfs_heights(i64 u, const vector<vector<i64>>& adj, i64 d, i64 p = -1){
        h[u] = d;
        parents[u] = p;
        for (i64 v: adj[u]){
            if (v == p) continue;
            dfs_heights(v, adj, d + 1, u);
        }
    }

    vector<i64> merge(const vector<i64>& a, const vector<i64>& b){
        vector<i64> c;
        vector<i64>::const_iterator it_a = a.begin(), it_b = b.begin();
        while (c.size() < A && (it_a != a.end() || it_b != b.end())){
            if (it_a == a.end()){
                c.emplace_back(*it_b);
                ++it_b;
            } else if (it_b == b.end()) {
                c.emplace_back(*it_a);
                ++it_a;
            } else if (*it_a < *it_b){
                c.emplace_back(*it_a);
                ++it_a;
            } else if (*it_a == *it_b) {
                c.emplace_back(*it_a);
                ++it_a;
                ++it_b;
            } else {
                c.emplace_back(*it_b);
                ++it_b;
            }
        }
        return c;
    }

    void build(){
        const i64 n = parents.size();
        i64 ilog = 0;
        while ((1ll << (ilog + 1)) <= n){
            ++ilog;
        }
        blift.assign(ilog + 1, vector<i64>(n, -1));
        lifted_min.assign(ilog + 1, vector<vector<i64>>(n));
        for (i64 u = 0; u < n; u++){
            blift[0][u] = parents[u];
            if (parents[u] != -1){
                lifted_min[0][u] = merge(init[u], init[parents[u]]);
            } else {
                lifted_min[0][u] = init[u];
            }
        }
        for (i64 j = 1; j <= ilog; j++){
            for (i64 u = 0; u < n; u++){
                if (blift[j - 1][u] != -1){
                    blift[j][u] = blift[j - 1][blift[j - 1][u]];
                    lifted_min[j][u] = merge(lifted_min[j - 1][u], lifted_min[j - 1][blift[j - 1][u]]);
                } else {
                    blift[j][u] = -1;
                    lifted_min[j][u] = lifted_min[j - 1][u];
                }
            }
        }
    }
};

void solve(){
    i64 n, m, q;
    cin >> n >> m >> q;

    vector<vector<i64>> adj(n);
    vector<vector<i64>> init(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }

    for (i64 i = 0; i < m; i++){
        i64 c;
        cin >> c;
        --c;
        if (init[c].size() < A){
            init[c].emplace_back(i);
        }
        sort(init[c].begin(), init[c].end());
        init[c].resize(min((i64)(init[c].size()), A));
    }

    LCA lca(adj, init);

    for (i64 i = 0; i < q; i++){
        i64 v, u, a;
        cin >> v >> u >> a;
        --v; --u;
        vector<i64> top_a = lca.query(u, v);
        cout << min((i64)top_a.size(), a) << " ";
        i64 j = 0;
        for (vector<i64>::iterator it = top_a.begin(); it != top_a.end() && j < a; it++, j++){
            cout << (*it) + 1 << " ";
        }
        cout << endl;
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
