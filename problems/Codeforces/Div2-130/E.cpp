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

void find_components(i64 u, i64 c, vector<vector<i64>> &tree, vector<i64> &components, i64 parent = -1){
    components[u] = c;
    for (i64 v: tree[u]){
        if (v == parent) continue;
        find_components(v, c, tree, components, u);
    }
}

struct LCA {
public:
    LCA(const vector<vector<i64>> &tree, i64 root = 0) : m_tree(tree), m_root(root){
        const i64 n = tree.size();
        m_first.resize(n);
        m_last.resize(n);
        m_height.resize(n);
        m_parents.resize(n);
        for (i64 i = 0; i < n; i++){
            m_parents[i] = i;
        }
        preprocess_dfs(root);
        build_sorted_lists();
        build_lifted_parents();
        // m_min_seg = MinSeg(m_euler_tour_heights);
    }
    //
    // i64 lca(const i64 a, const i64 b){
    //     i64 node_index = m_min_seg.argmin_query(min(m_first[a], m_first[b]), max(m_first[a], m_first[b]));
    //     return m_euler_tour_nodes[node_index];
    // }
    //
    // i64 lca_height(const i64 a, const i64 b){
    //     return m_min_seg.min_query(min(m_first[a], m_first[b]), max(m_first[a], m_first[b]));
    // }

    i64 query(i64 u, i64 deg){
        if (deg > m_height[u]){
            return 0;
        }
        i64 p = parent(u, deg);
        i64 l = m_first[p], r = m_last[p];
        i64 d = m_height[u];

        i64 discard_left = lower_bound(m_nodes_by_depth_end[d].begin(), m_nodes_by_depth_end[d].end(), l) - m_nodes_by_depth_end[d].begin();
        i64 discard_right = m_nodes_by_depth_start[d].size() - (lower_bound(m_nodes_by_depth_start[d].begin(), m_nodes_by_depth_start[d].end(), r + 1) - m_nodes_by_depth_start[d].begin());
        return m_nodes_by_depth_start[d].size() - discard_left - discard_right - 1;
    }
private:
    vector<vector<i64>> m_tree;
    i64 m_root;
    vector<i64> m_euler_tour_nodes, m_euler_tour_heights, m_first, m_last, m_height, m_parents;
    vector<vector<i64>> m_nodes_by_depth_start, m_nodes_by_depth_end;
    vector<vector<i64>> m_lifted_parents;

    // MinSeg m_min_seg;

    void preprocess_dfs(i64 u, i64 parent = -1, i64 height = 0) {
        m_height[u] = height;
        m_first[u] = m_euler_tour_nodes.size();
        m_last[u] = m_euler_tour_nodes.size();
        if (parent != -1){
            m_parents[u] = parent;
        }

        // entering
        m_euler_tour_nodes.emplace_back(u);
        m_euler_tour_heights.emplace_back(height);

        for (size_t i = 0; i < m_tree[u].size(); i++){
            i64 v = m_tree[u][i];
            if (v == parent) continue;  // in case the tree is undirected
            preprocess_dfs(v, u, height + 1);
            // coming back / backtracking
            m_last[u] = m_euler_tour_nodes.size();
            m_euler_tour_nodes.emplace_back(u);
            m_euler_tour_heights.emplace_back(height);
        }
    }

    void build_sorted_lists(){
        const i64 n = m_tree.size();
        i64 max_h = *max_element(m_height.begin(), m_height.end());
        m_nodes_by_depth_start.resize(max_h + 1);
        m_nodes_by_depth_end.resize(max_h + 1);
        for (i64 i = 0; i < n; i++){
            m_nodes_by_depth_start[m_height[i]].emplace_back(m_first[i]);
            m_nodes_by_depth_end[m_height[i]].emplace_back(m_last[i]);
        }
        for (i64 i = 0; i <= max_h; i++){
            sort(m_nodes_by_depth_start[i].begin(), m_nodes_by_depth_start[i].end());
            sort(m_nodes_by_depth_end[i].begin(), m_nodes_by_depth_end[i].end());
        }
    }

    void build_lifted_parents(){
        i64 max_height = *max_element(m_height.begin(), m_height.end());
        const i64 n = m_tree.size();
        i64 ilog = 0;
        while ((1ll << (ilog + 1)) <= max_height){
            ++ilog;
        }
        m_lifted_parents.assign(ilog + 1, vector<i64>(n));
        for (i64 i = 0; i < n; i++){
            m_lifted_parents[0][i] = m_parents[i];
        }
        for (i64 i = 1; i <= ilog; i++){
            for (i64 j = 0; j < n; j++){
                m_lifted_parents[i][j] = m_lifted_parents[i - 1][m_lifted_parents[i - 1][j]];
            }
        }
    }

    i64 parent(i64 u, i64 deg){
        i64 p = u;
        for (i64 i = 0; (1ll << i) <= deg; i++){
            if (deg & (1ll << i)){
                p = m_lifted_parents[i][p];
            }
        }
        return p;
    }
};


void solve(){
    i64 n;
    cin >> n;

    vector<vector<i64>> acyclic(n);
    for (i64 i = 0; i < n; i++){
        i64 a;
        cin >> a;
        --a;
        if (a == -1) continue;
        acyclic[a].emplace_back(i);
        acyclic[i].emplace_back(a);
    }

    i64 c = 0;
    vector<i64> components(n, -1);
    for (i64 i = 0; i < n; i++){
        if (components[i] == -1){
            find_components(i, c, acyclic, components);
            ++c;
        }
    }

    vector<vector<vector<i64>>> trees(c);
    vector<i64> max_component(c, -1);
    i64 translated[n];
    for (i64 i = 0; i < n; i++){
        translated[i] = max_component[components[i]] + 1;
        ++max_component[components[i]];
    }
    for (i64 i = 0; i < c; i++){
        trees[i].resize(max_component[i] + 1);
    }
    for (i64 u = 0; u < n; u++){
        for (i64 v: acyclic[u]){
            trees[components[u]][translated[u]].emplace_back(translated[v]);
        }
    }

    vector<LCA> lcas;
    for (i64 i = 0; i < c; i++){
        lcas.emplace_back(LCA(trees[i]));
    }

    i64 m;
    cin >> m;
    for (i64 i = 0; i < m; i++){
        i64 u, p;
        cin >> u >> p;
        --u;
        cout << lcas[components[u]].query(translated[u], p) << " ";
    }
    cout << endl;
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
