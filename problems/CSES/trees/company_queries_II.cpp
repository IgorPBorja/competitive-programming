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

const i64 INF = 1e18;

struct MinSeg {
public:
    MinSeg() {}
    MinSeg(vector<i64> a) : m_base(a){
        m_seg.resize(4 * (i64)a.size());
        m_argmin_seg.resize(4 * (i64)a.size());
        _build(0, (i64)a.size() - 1, 0);
    }
    // identity should be the identity element of this binary operation
    MinSeg(i64 n, i64 identity){
        m_base = vector<i64>(n, identity);
        m_seg.resize(4 * n);
        m_argmin_seg.resize(4 * n);
        _build(0, n - 1, 0);
    }

    i64 min_query(i64 l, i64 r){
        return _min_query(l, r, 0, (i64)m_base.size() - 1, 0);
    }

    i64 argmin_query(i64 l, i64 r){
        return _argmin_query(l, r, 0, (i64)m_base.size() - 1, 0);
    }

    void update(i64 p, i64 x){
        _update(p, x, 0, (i64)m_base.size() - 1, 0);
    }
private:
    vector<i64> m_seg;
    vector<i64> m_argmin_seg;
    vector<i64> m_base;

    void _build(i64 l, i64 r, i64 node){
        if (l == r){
            m_seg[node] = m_base[l];
            m_argmin_seg[node] = l;
        } else {
            const i64 m = l + (r - l) / 2;
            _build(l, m, 2 * node + 1);
            _build(m + 1, r, 2 * node + 2);
            m_seg[node] = min(m_seg[2 * node + 1], m_seg[2 * node + 2]);
            if (m_seg[2 * node + 1] <= m_seg[2 * node + 2]){
                m_argmin_seg[node] = m_argmin_seg[2 * node + 1];
            } else {
                m_argmin_seg[node] = m_argmin_seg[2 * node + 2];
            }
        }
    }

    i64 _min_query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (tl == l && tr == r){
            return m_seg[node];
        } else {
            i64 tm = tl + (tr - tl) / 2;
            if (r <= tm){
                return _min_query(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                return _min_query(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                return min(_min_query(l, tm, tl, tm, 2 * node + 1), _min_query(tm + 1, r, tm + 1, tr, 2 * node + 2));
            }
        }
    }

    i64 _argmin_query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr){
            return m_argmin_seg[node];
        } else {
            i64 tm = tl + (tr - tl) / 2;
            if (r <= tm){
                return _argmin_query(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                return _argmin_query(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                i64 left_argmin = _argmin_query(l, tm, tl, tm, 2 * node + 1);
                i64 right_argmin = _argmin_query(tm + 1, r, tm + 1, tr, 2 * node + 2);
                if (m_base[left_argmin] <= m_base[right_argmin]){
                    return left_argmin;
                } else {
                    return right_argmin;
                }
            }
        }
    }

    void _update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
        if (tl == p && p == tr){
            m_seg[node] = x;
            m_argmin_seg[node] = p;
            m_base[p] = x;
        } else {
            i64 tm = tl + (tr - tl) / 2;
            if (p <= tm){
                _update(p, x, tl, tm, 2 * node + 1);
            } else {
                _update(p, x, tm + 1, tr, 2 * node + 2);
            }
            m_seg[node] = min(m_seg[2 * node + 1], m_seg[2 * node + 2]);
            if (m_seg[2 * node + 1] <= m_seg[2 * node + 2]){
                m_argmin_seg[node] = m_argmin_seg[2 * node + 1];
            } else {
                m_argmin_seg[node] = m_argmin_seg[2 * node + 2];
            }
        }
    }
};

struct LCA {
public:
    LCA(const vector<vector<i64>> &tree, i64 root = 0) : m_tree(tree), m_root(root){
        const i64 n = tree.size();
        m_first.resize(n);
        m_height.resize(n);
        preprocess_dfs(root);
        m_min_seg = MinSeg(m_euler_tour_heights);
    }

    i64 lca(const i64 a, const i64 b){
        i64 node_index = m_min_seg.argmin_query(min(m_first[a], m_first[b]), max(m_first[a], m_first[b]));
        return m_euler_tour_nodes[node_index];
    }

    i64 lca_height(const i64 a, const i64 b){
        return m_min_seg.min_query(min(m_first[a], m_first[b]), max(m_first[a], m_first[b]));
    }
private:
    vector<vector<i64>> m_tree;
    i64 m_root;
    vector<i64> m_euler_tour_nodes, m_euler_tour_heights, m_first, m_height;
    MinSeg m_min_seg;

    void preprocess_dfs(i64 u, i64 parent = -1, i64 height = 0) {
        m_height[u] = height;
        m_first[u] = m_euler_tour_nodes.size();

        // entering
        m_euler_tour_nodes.emplace_back(u);
        m_euler_tour_heights.emplace_back(height);

        for (i64 v: m_tree[u]){
            if (v == parent) continue;  // in case the tree is undirected
            preprocess_dfs(v, u, height + 1);
            // coming back / backtracking
            m_euler_tour_nodes.emplace_back(u);
            m_euler_tour_heights.emplace_back(height);
        }
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;

    vector<vector<i64>> tree(n);
    for (i64 i = 1; i < n; i++){  // root is 0
        i64 p;
        cin >> p;
        --p;
        tree[p].emplace_back(i);
        tree[i].emplace_back(p);
    }

    LCA lca(tree);
    i64 a, b;
    for (i64 i = 0; i < q; i++){
        cin >> a >> b;
        --a; --b;
        cout << lca.lca(a, b) + 1 << endl;
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
