# Template/LIB para programação competitiva

# Binary lifting

```cpp
const int N = 2e5, LOGN = 20;
int lift[LOGN + 1][N];

void binary_lifting(const vector<vector<int>> &forest){
	const int n = forest.size();
	vector<int> parent(n, -1);
	for (int u = 0; u < n; u++){
		for (int v: forest[u]){
			parent[v] = u;
		}
	}
	for (int u = 0; u < n; u++){
		lift[0][u] = parent[u];
	}
	for (int k = 1; k <= LOGN; k++){
		for (int u = 0; u < n; u++){
			lift[k][u] = lift[k - 1][lift[k - 1][u]];
		}
	}
}

int jump(int u, int k){
	for (int i = 0; i <= LOGN; i++){
		if ((k >> i) & 1){
			u = lift[i][u];
		}
	}
	return u;
}
```

## LCA com binary lifting

```cpp
int LCA(
	int u, int v, const vector<int> &level,
	const vector<int> &parent
){
	// invariant: level[u] <= level[v]
	if (level[v] < level[u]) swap(u, v);
	v = jump(v, level[v] - level[u]);

	if (u == v){
		return u;
	}

	// loop invariant: u and v are distinct
	// (we have not reached a common ancestor yet)
	for (int i = LOGN; i >= 0; i--){
		if (lift[i][u] != lift[i][v]){
			// keeps loop invariant -> greedily take it!
			u = lift[i][u];
			v = lift[i][v];
		}
	}

	// at the end of the invariant we must be just one level below the LCA
	// otherwise we could have jumped more
	return parent[u];
}
```

# BIT

```cpp
vector<int> BIT(const vector<int> &a){
	int n = a.size();
	vector<int> B(n + 1, 0);

	for (int i = 0; i < n; i++){
		update(B, i, a[i]);  // sum a[i] to position i+1 of the BIT
	}
	return B;
}

int get(const vector<int> &BIT, int i){
	int s = 0;
	while (i >= 0){
		s += BIT[i];
		// i & -i == 2^lsb(i)
		i = i ^ (i & (-i));
	}
	return s;
}

void update(vector<int> &BIT, int i, int x){
	const int n = BIT.size() - 1;
	while (i <= n){
		BIT[i] += x;
		i += i & (-i);
	}
}
```

# DSU

```c++
struct DSU {
	vector<int> parent, sz;
	vector<vector<int>> elements;

	DSU(int n){
		parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
		sz.assign(n, 1);
		elements.resize(n);
		for (int i = 0; i < n; i++){
			elements[i].emplace_back(i);
		}
	}

	int find(int x){
		if (parent[x] != x){
			parent[x] = find(parent[x]);  // path-compression
		}
		return parent[x];
	}

	void unite(int x, int y){
		x = find(x);
		y = find(y);
		if (x == y){
			return;
		} else if (sz[x] > sz[y]) {
			swap(x, y);
		}
		sz[y] += sz[x];
		for (int z: elements[x]){
			elements[y].emplace_back(z);
		}
		parent[x] = y;
	}
};
```

# Detecção de ciclos

```c++
#define WHITE 0
#define GRAY 1
#define BLACK 2
bool has_cycle = false;

void dfs(vector<vector<int>> &g, int u, vector<int> &color){
	if (color[u] != WHITE){
		return;
	}
	color[u] = GRAY;
	for (int v: g[u]){
		if (color[v] == GRAY){
			has_cycle = true;
		} else if (color[v] == WHITE){
			dfs(g, u, color);
		}
	}
	color[u] = BLACK;
}
```

# Toposort

```c++
namespace Graph {
    i64 c;

    void dfs(
		i64 u, vector<vector<i64>> &G, vector<bool> &vis, vector<i64> &order
	){
        vis[u] = true;
        for (i64 v: G[u]){
            if (!vis[v]){
                dfs(v, G, vis, order);
            }
        }
        order[u] = c;
        --c;
    }

    vector<i64> toposort(vector<vector<i64>> &G){
        c = G.size() - 1;
        const i64 n = G.size();
        vector<bool> vis(n, false);
        vector<i64> order(n);
        for (i64 u = 0; u < n; u++){
            if (!vis[u]){
                dfs(u, G, vis, order);
            }
        }
        // validate order
        for (i64 u = 0; u < n; u++){
            for (i64 v: G[u]){
                if (order[u] >= order[v]) {
                    return vector<i64>();
                }
            }
        }
        return order;
    }
}
```

# Tarjan (for bridge deteccion)

```c++
namespace Tarjan {
    vector<int> lowlink, t_in;
    vector<pair<int, int>> dfs_tree_edges;
    int timer;

    void dfs(int u, const vector<vector<int>> &g, vector<bool> &vis,
			int parent = -1){
        vis[u] = true;
        t_in[u] = lowlink[u] = timer++;
        for (int to: g[u]){
            if (to == parent) continue;
            else if (vis[to]){
                // back edge on DFS tree
                lowlink[u] = min(t_in[to], lowlink[u]);
            } else {
                dfs(to, g, vis, u);
                dfs_tree_edges.emplace_back(u, to);
                lowlink[u] = min(lowlink[to], lowlink[u]);
            }
        }
    }

    // lowlink(u) = min(t_in(u), min_{p->u}t_in(u), min_{u->to em tree}lowlink(to))
    vector<vector<pair<int, int>>> dfs_tree_bridges(const vector<vector<int>> &g) {
        const int n = g.size();
        vector<bool> vis(n, false);
        lowlink = vector<int>(n, INF);
        t_in = vector<int>(n, INF);
        dfs_tree_edges.clear();
        timer = 0;

        for (int u = 0; u < n; u++){
            if (!vis[u]){
                dfs(u, g, vis);
            }
        }

        vector<vector<pair<int, int>>> h(n);
        for (auto[v, to]: dfs_tree_edges){
            if (lowlink[to] > t_in[v]){
                h[v].emplace_back(to, 1);
            } else {
                h[v].emplace_back(to, 0);
            }
        }
        return h;
    }
}
```

# Two Sat

```c++
namespace SAT2 {
    vector<vector<int>> build_graph(const vector<pair<int, int>> &clauses, int n){
        vector<vector<int>> g(2 * n);
        for (auto[x, y]: clauses){
            // (x or y) clause = (~x => y) clause and (~y => x) clause
            g[(x + n) % (2 * n)].emplace_back(y);
            g[(y + n) % (2 * n)].emplace_back(x);
        }
        return g;
    }
    vector<vector<int>> transpose(vector<vector<int>> &g){
        vector<vector<int>> gt(g.size());
        for (int u = 0; u < g.size(); u++){
            for (int v: g[u]){
                gt[v].emplace_back(u);
            }
        }
        return gt;
    }

    void forward_dfs(
		const int u, vector<vector<int>> &g, vector<bool> &vis, vector<int> &stack
	){
        vis[u] = true;
        for (int v: g[u]){
            if (!vis[v]){
                forward_dfs(v, g, vis, stack);
            }
        }
        stack.emplace_back(u);
    }

    void backward_dfs(
		const int u, vector<vector<int>> &g, vector<bool> &vis,
		vector<int> &comp, int c = 0
	){
        vis[u] = true;
        comp[u] = c;
        for (int v: g[u]){
            if (!vis[v]){
                backward_dfs(v, g, vis, comp, c);
            }
        }
    }

    pair<vector<int>, int> scc(const vector<pair<int, int>> &clauses, int n){
        vector<vector<int>> g = build_graph(clauses, n);
        vector<vector<int>> gt = transpose(g);

        const int s = g.size();
        vector<int> stack, comp(s);
        vector<bool> vis(s, false);
        for (int u = 0; u < s; u++){
            if (!vis[u]){
                forward_dfs(u, g, vis, stack);
            }
        }
        reverse(stack.begin(), stack.end());
        fill(vis.begin(), vis.end(), false);
        int c = 0;
        for (int u: stack){
            if (!vis[u]){
                backward_dfs(u, gt, vis, comp, c);
                ++c;
            }
        }
        return {comp, c};
    }

    pair<vector<bool>, bool> solve(const vector<pair<int, int>>& clauses, int n){
        // run scc (Kosaraju)
        auto[comp, num_comps] = scc(clauses, n);

        // build quotient graph
        vector<vector<int>> g_scc(num_comps);
        for (auto[x, y]: clauses){
            // (x or y) = (~x => y) = (~y => x)
            g_scc[comp[(x + n) % (2 * n)]].emplace_back(comp[y]);
            g_scc[comp[(y + n) % (2 * n)]].emplace_back(comp[x]);
        }

        // build valuation: mark as true the first one that appears
        vector<bool> valuation(n);
        for (int u = 0; u < n; u++){
            if (comp[u] < comp[u + n]){
                valuation[u] = false;
            } else {
                valuation[u] = true;
            }
        }

        // check valuation
        bool ok = true;
        for (auto[x, y]: clauses){
            bool left = ((x < n) ? valuation[x] : !valuation[x - n]);
            bool right = ((y < n) ? valuation[y] : !valuation[y - n]);
            ok &= left | right;
        }
        return {valuation, ok};
    }
};
```

# SCC (Kosaraju)

```c++
vector<vector<int>> transpose(const vector<vector<int>> &g){
	vector<vector<int>> gt(g.size());
	for (int u = 0; u < g.size(); u++){
		for (int v: g[u]){
			gt[v].emplace_back(u);
		}
	}
	return gt;
}

void forward_dfs(
	const int u, const vector<vector<int>> &g, vector<bool> &vis, vector<int> &stack
){
	vis[u] = true;
	for (int v: g[u]){
		if (!vis[v]){
			forward_dfs(v, g, vis, stack);
		}
	}
	stack.emplace_back(u);
}

void backward_dfs(
	const int u, const vector<vector<int>> &g, vector<bool> &vis,
	vector<int> &comp, int c = 0
){
	vis[u] = true;
	comp[u] = c;
	for (int v: g[u]){
		if (!vis[v]){
			backward_dfs(v, g, vis, comp, c);
		}
	}
}

pair<vector<int>, int> scc(const vector<vector<int>> &g, int n){
	vector<vector<int>> gt = transpose(g);

	const int s = g.size();
	vector<int> stack, comp(s);
	vector<bool> vis(s, false);
	for (int u = 0; u < s; u++){
		if (!vis[u]){
			forward_dfs(u, g, vis, stack);
		}
	}
	reverse(stack.begin(), stack.end());
	fill(vis.begin(), vis.end(), false);
	int c = 0;
	for (int u: stack){
		if (!vis[u]){
			backward_dfs(u, gt, vis, comp, c);
			++c;
		}
	}
	return {comp, c};
}
```

# SegTree padrão (aqui um exemplo de MaxSeg)

```c++
const int INF = (int)2e9;
 
struct MaxSegTree {
    vector<i64> seg;
    vector<i64> a;
    i64 n;

    MaxSegTree(i64 n, i64 val = -INF) : n(n) {
        seg.assign(4 * n, val);
        a.assign(n, val);
    }

    i64 query(i64 l, i64 r){
        return _query(l, r, 0, n - 1, 0);
    }

    void update(i64 p, i64 x){
        _update(p, x, 0, n - 1, 0);
    }

private:
    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr){
            return seg[node];
        } else {
            i64 tm = tl + (tr - tl) / 2;
            if (r <= tm){
                return _query(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                return _query(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                return max(
					_query(l, tm, tl, tm, 2 * node + 1),
					_query(tm + 1, r, tm + 1, tr, 2 * node + 2)
				);
            }
        }
    }

    void _update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
        if (tl == p && tr == p){
            seg[node] = x;
            a[p] = x;
        } else {
            i64 tm = tl + (tr - tl) / 2;
            if (p <= tm){
                _update(p, x, tl, tm, 2 * node + 1);
            } else {
                _update(p, x, tm + 1, tr, 2 * node + 2);
            }
            seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }
};
```

# Dijkstra

```c++
const int INF = (int)2e9;

// directed edges are pairs (weight, endpoint)
void dijkstra(vector<vector<pair<int, int>>> &adj, int dis[], int s)
{
    for (int i = 0; i < (int)adj.size(); i++) dis[i] = INF;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
    pq.emplace(0, s);
    dis[s] = 0;
    while (!pq.empty())
    {
        auto [dis_u, u] = pq.top();
        pq.pop();
        if (dis_u > dis[u]) 
            continue; // skip suboptimal
        // since dis[u] is always updated when better path is found,
        // dis[u] <= d for each [d, u] state on the priority queue

        for (auto [w, v] : adj[u])
        {
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                pq.emplace(dis[v], v); 
                // sorting by dis[v] is the same as sorting by the weights w[u, v]
                // since dis[v] - w(u, v) = dis[u] for all v (constant difference)
            }
        }
    }
}
```

# Detecção de ciclos negativos com Bellman-Ford em $O(VE)$

```c++
// edges: (a, b, c) = directed edge from a to b with weight c
vector<int> negative_cycle(const vector<tuple<int, int, int>> edges, int n){
    // virtual vertex connects to all others with weight 0
    // so ALL negative cycles are reachable!
    // for that effect we just need to set d[u] = 0 for all u
    // (we don't need an actual new vertex)
    vector<int> d(n, 0);
    vector<int> source_list;
    vector<int> prev(n, -1);
    // all paths of size s
    for (int s = 0; s <= n; s++){
        bool any = false;
        for (auto[a, b, c]: edges){
            if (d[a] + c < d[b]){
                any = true;
                prev[b] = a;
                d[b] = d[a] + c;
            }
        }
        if (!any) break;
    }
 
    // run a (single) new iteration of relaxation
    int target = -1;
    for (auto[a, b, c]: edges){
        if (d[a] + c < d[b]){
            target = b;
            break;
        }
    }
    if (target != -1){
        vector<int> cyc;
        // might be a cycle end or a vertex reachable from a negative cycle
        int curr = target;
        vector<bool> vis(n);
        while (!vis[curr]) {
            cyc.emplace_back(curr);
            vis[curr] = true;
            // we might have prev[curr] == curr
            // (in case of self negative edges!)
            curr = prev[curr];
        }
        // now curr is a visited vertex (closed the cycle!)
        cyc.emplace_back(curr);
        reverse(cyc.begin(), cyc.end());
        while (cyc.back() != cyc[0]){
            cyc.pop_back(); // remove vertices reachable from the cycle but not in it
        }
        return cyc;
    } else {
		return vector<int>();
	}
}
```

# Floyd-Warshall $O(V^3)$ (from cp-algorithms)

```c++
const int INF = (int)2e9;  // might change depending on the problem

vector<vector<int>> floydWarshall(const vector<tuple<int, int, int>>& edges, int n){
	vector<vector<int>> d(n, vector<int>(n, INF));
	for (int i = 0; i < n; i++){
		d[i][i] = 0;
	}
	for (auto[a, b, w]: edges){
		d[a][b] = min(d[a][b], w);
	}
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (d[i][k] < INF && d[k][j] < INF)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
			}
		}
	}
	return d;
}
```

# Binary exponentiation and modular inverse

```c++
const int MOD = (int)1e9 + 7;  // NOTE: MIGHT CHANGE

int bexp(int a, int p){
    if (p == 0){
        return 1;
    } else {
        int m = bexp(a, p / 2);
        if (p % 2 == 1){
            return (((m * m) % MOD) * a) % MOD;
        } else {
            return (m * m) % MOD;
        }
    }
}

int inv(int a){
    return bexp(a, MOD - 2);
}
```

# FFT (from cp-algorithms)

```c++
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
```

# Template (generic) for every problem

```c++
#define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
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

void solve(){

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
```
