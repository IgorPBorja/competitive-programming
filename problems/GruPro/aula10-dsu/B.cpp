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

struct DSU {
	vector<i64> parent, sz;
    i64 comp;

	DSU(i64 n) : comp(n) {
		parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
		sz.assign(n, 1);
	}

	i64 find(i64 x){
		if (parent[x] != x){
			parent[x] = find(parent[x]);  // path-compression
		}
		return parent[x];
	}

	void unite(i64 x, i64 y){
		x = find(x);
		y = find(y);
		if (x == y){
			return;
		} else if (sz[x] > sz[y]) {
			swap(x, y);
		}
		sz[y] += sz[x];
		parent[x] = y;
        --comp;
	}
};

namespace Toposort {
    i64 c;

    void dfs(i64 u, const vector<vector<i64>> &adj, vector<bool> &vis, vector<i64> &order){
        vis[u] = true;
        for (i64 v: adj[u]){
            if (!vis[v]) dfs(v, adj, vis, order);
        }
        order[u] = c;
        --c;
    }

    vector<i64> sort(const vector<vector<i64>> &adj){
        const i64 n = adj.size();
        vector<bool> vis(n, false);
        vector<i64> order(n);
        c = n - 1;
        for (i64 u = 0; u < n; u++){
            if (!vis[u]) dfs(u, adj, vis, order);
        }
        return order;
    }
}


void solve(){
    i64 n, m, k, w;
    cin >> n >> m >> k >> w;

    char a[k][n][m];
    for (i64 i = 0; i < k; i++){
        for (i64 r = 0; r < n; r++){
            string row;
            cin >> row;
            for (i64 c = 0; c < m; c++){
                a[i][r][c] = row[c];
            }
        }
    }

    i64 diff[k][k];

    for (i64 i = 0; i < k; i++){
        for (i64 j = 0; j < k; j++){
            // calculate diff
            diff[i][j] = 0;
            for (i64 r = 0; r < n; r++){
                for (i64 c = 0; c < m; c++){
                    diff[i][j] += w * ((a[i][r][c] != a[j][r][c]) ? 1 : 0);
                }
            }
        }
    }

    vector<tuple<i64, i64, i64>> edges;
    for (i64 i = 0; i < k; i++){
        edges.emplace_back(n * m, 0, i + 1);
        edges.emplace_back(n * m, i + 1, 0);
    }
    for (i64 i = 0; i < k; i++){
        for (i64 j = 0; j < k; j++){
            if (i == j) continue;
            edges.emplace_back(diff[i][j], i + 1, j + 1);
        }
    }

    sort(edges.begin(), edges.end());
    DSU mst(k + 1);
    i64 mst_cost = 0;
    vector<pair<i64, i64>> mst_edges;
    vector<vector<i64>> mst_graph(k + 1);
    for (auto[c, a, b]: edges){
        if (mst.comp == 1) break;
        if (mst.find(a) != mst.find(b)){
            mst_edges.emplace_back(a, b);
            mst_cost += c;
            mst.unite(a, b);
            mst_graph[a].emplace_back(b);
            mst_graph[b].emplace_back(a);
        }
    }
    // printgraph("mst=", mst_graph);
    vector<i64> order = Toposort::sort(mst_graph);
    // printmsg("order=", order.begin(), order.end());
    sort(mst_edges.begin(), mst_edges.end(), [&order](auto e1, auto e2){
            return min(order[e1.first], order[e1.second]) < min(order[e2.first], order[e2.second]);
            });

    cout << mst_cost << endl;
    for (auto[a, b]: mst_edges){
        // a -> b
        if (order[a] < order[b]){
            cout << b << " " << a << endl;
        } else {
            cout << a << " " << b << endl;
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
