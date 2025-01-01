#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

#define printmsg(msg, first, last) \
    cerr << msg; \
    for (auto it = first; it != last; it++) cerr << *it << " "; \
    cerr << endl

#define printgraph(name, g) \
    for (size_t u = 0; u < sizeof(g) / sizeof(g[0]); u++){ \
        cout << name << "[" << u << "]="; \
        for (auto v: g[u]){ \
            cout << v << " "; \
        } \
        cout << endl; \
    }

i64 MOD;

void dfs_down(i64 u, const vector<vector<i64>>& g, i64 down[], i64 p_array[], i64 p = -1){
    down[u] = 1;
    for (i64 v: g[u]){
        if (v == p) continue;
        p_array[v] = u;
        dfs_down(v, g, down, p_array, u);
        down[u] = (down[u] * (1 + down[v])) % MOD;
    }
}

void acc_down(
    const vector<vector<i64>>& g, vector<i64> pref_down[], vector<i64> suf_down[], i64 down[], i64 p[]
){
    const i64 n = g.size();
    for (i64 u = 0; u < n; u++){
        pref_down[u].resize(g[u].size() + 1);  // exclusive prefix
        suf_down[u].resize(g[u].size() + 1);

        pref_down[u][0] = 1;
        for (i64 i = 0; i < g[u].size(); i++){
            if (g[u][i] == p[u]){
                // is parent, skip it
                pref_down[u][i + 1] = pref_down[u][i];
            } else {
                pref_down[u][i + 1] = (pref_down[u][i] * (1 + down[g[u][i]])) % MOD;
            }
        }

        suf_down[u][(i64)g[u].size()] = 1;
        for (i64 i = (i64)g[u].size() - 1; i >= 0; i--){
            if (g[u][i] == p[u]){
                // is parent, skip it
                suf_down[u][i] = suf_down[u][i + 1];
            } else {
                suf_down[u][i] = (suf_down[u][i + 1] * (1 + down[g[u][i]])) % MOD;
            }
        }
    }
}

void dfs_up(
    i64 u, const vector<vector<i64>>& g,
    i64 up[], i64 down[],
    vector<i64> pref_down[],
    vector<i64> suf_down[],
    i64 p = -1
){
    if (p == -1){
        up[u] = 1;
    } else {
        // up[u] = 1 + up[p[u]] * prod(p[u] -> v, v != u) (1 + down[v])
        // this product can be broken into what comes before and after u
        i64 u_idx = lower_bound(g[p].begin(), g[p].end(), u) - g[p].begin();  // definitely valid idx
        i64 prod = (pref_down[p][u_idx] * suf_down[p][u_idx + 1]) % MOD;
        up[u] = (1 + ((up[p] * prod) % MOD)) % MOD;
    }
    for (i64 v: g[u]){
        if (v == p) continue;
        dfs_up(v, g, up, down, pref_down, suf_down, u);
    }
}

void solve(){
    i64 n;
    cin >> n;
    cin >> MOD;  // NOTE: global
    vector<vector<i64>> g(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for (i64 u = 0; u < n; u++){
        sort(g[u].begin(), g[u].end());
    }
    i64 down[n], up[n], parents[n];
    vector<i64> pref_down[n], suf_down[n];
    const i64 ROOT = 0;
    dfs_down(ROOT, g, down, parents);
    acc_down(g, pref_down, suf_down, down, parents);
    dfs_up(ROOT, g, up, down, pref_down, suf_down);
    for (i64 u = 0; u < n; u++){
        cout << (down[u] * up[u]) % MOD << endl;
    }
}

signed main(){
    solve();
}
