#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<class T> using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define dbg(x) cerr << #x << " = " << x << endl;
#define int long long
#define double long double
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(),a.rend()
#define endl "\n"
#define i64 int64_t
#define debug cerr
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
const int mod = 1e9 + 7, mod2 = 998244353;
const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };     

struct Tree {
    vector<vector<i64>> adj;
    vector<i64> p, sz;
    i64 root;
    i64 n;
    i64 max_depth;
    i64 final_leaf;

    Tree(const vector<vector<i64>>& _adj, i64 _root) : adj(_adj), root(_root), n(_adj.size()) {
        max_depth = -1;
        sz.resize(n);
        p.resize(n);
        dfs_max_depth(root);
    }

    void dfs_max_depth(i64 u, i64 parent = -1, i64 d = 0){
        sz[u] = 1;
        if (d > max_depth){
            final_leaf = u;
            max_depth = d;
        }
        p[u] = parent;
        for (i64 v: adj[u]){
            dfs_max_depth(v, u, d + 1);
            sz[u] += sz[v];
        }
    }

    void dfs_build_adj(i64 u, vector<vector<i64>>& subtree_adj, vector<i64>& nodes){
        // cerr << "at u=" << u << endl;
        // printmsg("adj[u]=", adj[u].begin(), adj[u].end());
        i64 u_idx = lower_bound(all(nodes), u) - nodes.begin();
        for (i64 v: adj[u]){
            i64 v_idx = lower_bound(all(nodes), v) - nodes.begin();
            subtree_adj[u_idx].emplace_back(v_idx);
            dfs_build_adj(v, subtree_adj, nodes);
        }
    }

    void dfs_build_list(i64 u, vector<i64>& nodes){
        nodes.emplace_back(u);
        for (i64 v: adj[u]){
            dfs_build_list(v, nodes);
        }
    }

    vector<Tree> split(i64 leaf){
        vector<i64> exclude(n);
        vector<i64> exclude_list;
        i64 cur = leaf;
        while (cur != -1){
            exclude[cur] = true;
            exclude_list.emplace_back(cur);
            cur = p[cur];
        }
        reverse(all(exclude_list));
        // cerr << "exclude ok" << endl;

        vector<Tree> ans;
        for (i64 u: exclude_list){
            for (i64 v: adj[u]){
                if (v == p[u]) continue;
                if (exclude[v]) continue;
                // cerr << "at v=" << v << endl;
                // child of deleted node, not deleted itself
                vector<i64> nodes;
                vector<vector<i64>> subtree_adj(sz[v]);
                dfs_build_list(v, nodes);
                sort(all(nodes));
                dfs_build_adj(v, subtree_adj, nodes);
                i64 v_idx = lower_bound(all(nodes), v) - nodes.begin();
                // cerr << "split at v" << endl;
                ans.emplace_back(subtree_adj, v_idx);
                // cerr << "v ok" << endl;
            }
        }
        return ans;
    }
};

void solve(){
    i64 n, k;
    cin >> n >> k;
    vector<vector<i64>> adj(n);
    for (i64 i = 1; i < n; i++){
        i64 j;
        cin >> j;
        --j;
        // p[i] = j
        adj[j].emplace_back(i);
    }
    // cerr << "read ok" << endl;
    vector<Tree> global;
    set<pair<i64, i64>, greater<>> s;
    global.emplace_back(adj, 0);
    s.emplace(global[0].max_depth, 0);
    // cerr << "built first" << endl;
    // cerr << "final leaf=" << global[0].final_leaf << endl;
    // cerr << "max depth=" << global[0].max_depth << endl;

    i64 ans = 0;
    for (i64 _ = 0; _ < k && !s.empty(); _++){
        auto[d, T] = *s.begin();
        // cerr << "rooted at root=" << global[T].root << " with longest path=" << d + 1 << endl;
        s.erase(s.begin());
        ans += d + 1;
        vector<Tree> parts = global[T].split(global[T].final_leaf);
        // cerr << "split ok" << endl;
        for (const auto& subT: parts){
            s.emplace(subT.max_depth, global.size());
            global.emplace_back(subT);
        }
        // cerr << "emplace ok" << endl;
    }
    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
