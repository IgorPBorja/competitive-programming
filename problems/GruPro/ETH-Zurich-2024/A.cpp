#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'

vector<vector<i64>> rooted_tree;
vector<i64> parent;
vector<i64> deg, depth;
const i64 MAXN = (i64)1e5 + 1;
const i64 MOD = 998244353;
const i64 MAX_LOG = 20;

i64 plift[MAX_LOG + 1][MAXN + 1]; // plift[i][j] = p^{2^i}(j)
i64 compose[MAX_LOG + 1][MAXN + 1];
// compose[i][j] = (deg[p^1(j)] - 1) * ... * (deg[p^{2^i}(j)] - 1) mod MOD
// (so exclusive on the first half)
// it is 1 in case of root (j=root)

void setup_lca(){
    const i64 n = parent.size();
    for (i64 i = 0; i < n; i++){
        plift[0][i] = (parent[i] == -1) ? i : parent[i];
        compose[0][i] = (parent[i] == -1) ? 1 : ((deg[parent[i]] + MOD - 1) % MOD);
    }
    
    for (i64 i = 1; i <= MAX_LOG; i++){
        for (i64 j = 0; j < n; j++){
            plift[i][j] = (plift[i-1][j] == -1) ? -1 : plift[i - 1][plift[i - 1][j]];
            // prod() (deg[p^k(j)] - 1) = 
            // prod(k=1...2^{i-1})(deg[p^k(j)] - 1) * prod(k=1...2^{i-1})(deg[p^k(p^{2^{i-1}}(j))] - 1)
            // except if p^{2^{i-1}}(j) is not a real node, so plift[i-1][j] == -1
            compose[i][j] = compose[i - 1][j];
            if (plift[i-1][j] != -1){
                compose[i][j] = (compose[i][j] * compose[i - 1][plift[i - 1][j]]) % MOD;
            }
        }
    }
}

// assumes always called with delta <= depth[u]
i64 query_parent(i64 u, i64 delta){
    for (i64 i = MAX_LOG; i >= 0; i--){
        if (delta & (1ll << i)){
            u = plift[i][u];
        }
    }
    return u;
}

// assumes always called with delta <= depth[u]
// prod(k=1...delta)(deg[p^k(u)] - 1) % MOD
i64 query_prod(i64 u, i64 delta){
    i64 p = 1, node = u;
    for (i64 i = MAX_LOG; i >= 0; i--){
        if (delta & (1ll << i)){
            // at node, need node+1...node+2^i
            p = (p * compose[i][node]) % MOD;
            node = plift[i][node];
        }
    }
    return p;
}


i64 query_path(i64 u, i64 v){
    i64 diff = max(depth[u] - depth[v], depth[v] - depth[u]);
    i64 ans = 1;
    if (depth[u] > depth[v] && query_parent(u, diff) == v){
        // direct path up from u to v
        ans = query_prod(u, diff - 1); // up to but not including v
        // include deg[u]
        ans = (ans * deg[u]) % MOD;
        return ans;
    } else if (depth[v] > depth[u] && query_parent(v, diff) == u){
        // direct path up from v to u
        ans = query_prod(v, diff - 1); // up to but not including u
        // include deg[u]
        ans = (ans * deg[u]) % MOD;
        return ans;
    } else if (depth[u] > depth[v]){
        // u needs going up, but not on the same chain
        ans = query_prod(u, diff);
        // include deg[u]
        ans = (ans * deg[u]) % MOD;
        u = query_parent(u, diff);
    } else if (depth[v] > depth[u]){
        // v needs going up, but not on the same chain
        ans = query_prod(v, diff);
        // include deg[u]
        ans = (ans * deg[u]) % MOD;
        v = query_parent(v, diff);
    } else if (depth[u] == depth[v]){
        // since u != v, definitely different subtrees
        ans = deg[u] % MOD;
    }

    // can assume d[u] = d[v] from now on
    for (i64 i = MAX_LOG; i >= 0; i--){
        if (plift[i][u] != plift[i][v]){
            ans = (ans * compose[i][u]) % MOD;
            ans = (ans * compose[i][v]) % MOD;
            u = plift[i][u];
            v = plift[i][v];
        }
    }
    // now both u, v are direct children of LCA
    // so it should multiply by (deg[LCA] - 1)
    i64 lca = parent[u];
    ans = (ans * (deg[lca] + MOD - 1) % MOD);
    return ans;
}


void root(const vector<vector<i64>>& tree, i64 u = 0, i64 p = -1, i64 d = 0){
    parent[u] = p;
    depth[u] = d;
    for (i64 v: tree[u]){
        if (v == p) continue;
        rooted_tree[u].emplace_back(v);
        root(tree, v, u, d + 1);
    }
}


int main(){
    fastio;

    i64 n, q;
    cin >> n >> q;
    vector<vector<i64>> tree(n);
    for (i64 i = 0; i < n - 1; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }
    deg.resize(n);
    for (i64 i = 0; i < n; i++){
        deg[i] = tree[i].size();
    }
    rooted_tree.resize(n);
    parent.resize(n);
    depth.resize(n);
    root(tree);
    // cerr << "root ok" << endl;
    setup_lca();
    // cerr << "setup ok" << endl;
    
    for (i64 i = 0; i < q; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        cout << query_path(a, b) << endl;
    }
}