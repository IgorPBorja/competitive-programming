#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define printmsg(msg, first, last) \
    cerr << msg; \
    for (auto it = first; it != last; it++) { \
        cerr << *it << " "; \
    } \
    cerr << endl

const i64 MAXN = (i64)1e5 + 10, MAXQ = (i64)1e5 + 10;
const i64 ROOT = 0;
const i64 INF = (i64)2e18;
i64 n, q;
i64 f[MAXN], t[MAXN];
i64 claims[MAXN];
vector<pair<i64, i64>> queries_per_endpoint[MAXN];
i64 ans[MAXQ];

void move_root(i64 u, i64 v, i64 w){
    // NOTE: if u->v down then f[u] and f[v] are in different subtrees obviously (same if v->u down)

    // We steal v iff (t[u] + w, f[u]) < (t[v], f[v]) OR u is in the f[v]->v path
    // (which happens iff f[v] is in the u subtree)
    // in that case,
    // in case f[v] stops going to u
    // if f[u] is better OR f[v] was in 
    if (make_pair(t[u] + w, f[u]) < make_pair(t[v], f[v])){
        --claims[f[v]];
        ++claims[f[u]];
        f[v] = f[u];
        t[v] = t[u] + w;
    }
    // steal u
    else if (make_pair(t[v] + w, f[v]) < make_pair(t[u], f[u])){
        --claims[f[u]];
        ++claims[f[v]];
        f[u] = f[v];
        t[u] = t[v] + w;
    }
}

// initial dfs
void dfs_1(i64 u, const vector<vector<pair<i64, i64>>>& g, i64 p = -1){
    if (g[u].size() == 1){
        // leaf vertex from unrooted perspective (so any with deg=1)
        f[u] = u;
        t[u] = 0;
        ++claims[u];
        // compute on others in case it is root, not real directed leaf
        if (g[u][0].second != p){
            dfs_1(g[u][0].second, g, u);
        }
    } else {
        pair<i64, i64> best = make_pair(INF, INF);
        for (auto[w, v]: g[u]){
            if (v == p) continue;
            dfs_1(v, g, u);
            best = min(best, make_pair(t[v] + w, f[v]));
        }
        // register claim
        t[u] = best.first;
        f[u] = best.second;
        ++claims[f[u]];
        cerr << f[u] + 1 << " claims " << u + 1 << endl;
    }
}

// rerooting dfs
void dfs_reroot(i64 u, const vector<vector<pair<i64, i64>>>& g, i64 p = -1){
    // answer queries
    for (auto[s, idx]: queries_per_endpoint[u]){
        ans[idx] = claims[s];
    }
    printmsg("at endpoint u=" << u << " claims=", claims, claims + g.size());
    // move roots
    for (auto[w, v]: g[u]){
        if (v == p) continue;
        // save to undo later
        i64 claims_fu = claims[f[u]], claims_fv = claims[f[v]],
            fu = f[u], fv = f[v],
            tu = t[u], tv = t[v];
        move_root(u, v, w);
        dfs_reroot(v, g, u);
        // undo move
        f[u] = fu;
        f[v] = fv;
        t[u] = tu;
        t[v] = tv;
        claims[fu] = claims_fu;
        claims[fv] = claims_fv;
    }
}

signed main(){
    memset(claims, 0, sizeof(claims));

    cin >> n;
    vector<vector<pair<i64, i64>>> g(n);  // (w, v)
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        g[u].emplace_back(w, v);
        g[v].emplace_back(w, u);
    }

    cin >> q;
    for (i64 i = 0; i < q; i++){
        i64 s, t;
        cin >> s >> t;
        --s; --t;
        queries_per_endpoint[t].emplace_back(s, i);
    }

    // initial calculation
    dfs_1(ROOT, g);
    printmsg("initially we have claims=", claims, claims + g.size());

    // dfs for moving root one edge at a time
    dfs_reroot(ROOT, g);

    for (i64 i = 0; i < q; i++){
        cout << ans[i] << endl;
    }
}