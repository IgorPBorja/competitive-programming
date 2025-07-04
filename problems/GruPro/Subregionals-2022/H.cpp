// #define testcases
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define printmsg(msg, first, last) \
    cerr << msg; \
    for (auto it = first; it != last; it++) { \
        cerr << *it << " "; \
    } \
    cerr << endl
#define printgraph(msg, graph) \
    cerr << msg << endl; \
    for (i64 u = 0; u < graph.size(); u++) { \
        for (i64 v: graph[u]) { \
            cerr << "    " << u << "->" << v << endl; \
        } \
    } \
    cerr << endl

const i64 INF = (i64)2e18;

template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> p){
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

namespace quotient {
    using graph = vector<vector<i64>>;
    /*
    Kosaraju for SCC:
    - dfs and push after visit
    - stack will have reverse toposort
    - reverse stack
    - do dfs on inverse graph
    */

    void dfs_forward(const graph& G, vector<i64>& vis, i64 u, vector<i64>& stack){
        vis[u] = true;
        for (i64 v: G[u]){
            if (!vis[v]) dfs_forward(G, vis, v, stack);
        }
        stack.emplace_back(u);
    }

    void dfs_backward(const graph& Gr, vector<i64>& vis, i64 u, vector<i64>& component_assignment, i64 c){
        vis[u] = true;
        component_assignment[u] = c;
        for (i64 v: Gr[u]){
            if (!vis[v]) dfs_backward(Gr, vis, v, component_assignment, c);
        }
    }

    graph quotient(const graph& G){
        const i64 n = G.size();
        graph Gr(n);
        for (i64 u = 0; u < n; u++){
            for (i64 v: G[u]) Gr[v].emplace_back(u);
        }

        vector<i64> stack;
        vector<i64> vis(n, false);
        for (i64 u = 0; u < n; u++){
            if (!vis[u]) dfs_forward(G, vis, u, stack);
        }
        reverse(stack.begin(), stack.end());

        fill(vis.begin(), vis.end(), false);
        vector<i64> comp(n, -1);
        i64 c = 0;
        for (i64 u: stack){
            if (vis[u]) continue;
            dfs_backward(Gr, vis, u, comp, c);
            ++c;
        }

        vector<set<i64>> _Gq(c);
        for (i64 u = 0; u < n; u++){
            for (i64 v: G[u]){
                if (comp[u] != comp[v]){
                    _Gq[comp[u]].insert(comp[v]);
                }
            }
        }
        graph Gq(c);
        for (i64 u = 0; u < c; u++){
            for (i64 v: _Gq[u]) Gq[u].emplace_back(v);
        }
        return Gq;
    }
}

void solve(){
    i64 n, m;
    cin >> n >> m;

    vector<vector<i64>> adj(n);
    for (i64 i = 0; i < m; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
    }
    vector<vector<i64>> Gq = quotient::quotient(adj);
    const i64 k = Gq.size();
    if (k == 1) {
        // edge case, already connected
        cout << 0 << endl;
        return;
    }
    vector<vector<i64>> Gq_r(k);
    for (i64 u = 0; u < k; u++) {
        for (i64 v: Gq[u]) Gq_r[v].emplace_back(u);
    }

    i64 src = 0, sink = 0;
    for (i64 u = 0; u < k; u++) {
        sink += Gq[u].empty();  // deg out = 0
        src += Gq_r[u].empty();  // deg in = 0
    }
    // greedy optimal approach for full connectivity
    // connect sink i to src i for i=1..min(src,sink)
    // Then if src > sink connect sink 1 to src j for j=sink+1..src
    // or if sink > src connect sink j to src 1 for j=src+1..sink
    // Total: max(src, sink) edges
    cout << max(src, sink) << endl;
}

signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}

