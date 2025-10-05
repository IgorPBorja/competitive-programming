// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) debug << msg; for(auto it = v.begin(); it != v.end(); it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (auto v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

/*
We know for every a[i][j] > 1 we have a cost of 1 for at least a[i][j]-1 elements.
So we have a total of T = sum(i)sum(j)max(a[i][j] - 1, 0) stones to move

Now, we have two options on the additional cost:
* if we move stone from (i,j) to (x,y) and i=x or j=y, cost is 0
* else if i != x and j != y, cost is 1

(naturally a[x][y] = 0, since we want to fill someone unfilled)

Thus greedily we want to maximize the (i, j) -> (x, y) transitions where i=x and j=y. Let's
build the graph containing only those transitions and run max flow. Let A = {(i, j): a[i][j] > 1} e B = {(i, j): a[i][j] = 0}
Then lets do

source s -> any vertex (i, j) in A with capacity a[i][j] - 1
(i, j) in A -> row i with infinite capacity
(i, j) in A -> col j with infinite capacity
row i -> (i, j) in B with infinite capacity
col j -> (i, j) in B with infinite capacity
(i, j) in B -> sink t with capacity 1

row i indicates that we took some transition that stayed in row i, and went to any col
col j indicates that we took some transition that stayed in col j, and went to any row

There are O(|A| + |B|) = O(n^2) edges and vertices, and worst case COULD be O(V^2 * E) = O(n^4)
However, dinic is usually much faster.

We know that we have to move T stones. Maxflow F on this network
says how many of those will be moved in 1 step, so final cost is
ANS = F + 2 * (T - F)
*/

const i64 INF = (i64)2e18;
struct Edge {
    i64 u, v, c, f;
    i64 cap(){ return c - f; }
    Edge(i64 from, i64 to, i64 cap, i64 flow) : u(from), v(to), c(cap), f(flow) {}
};

// for edge indices 0..m-1 in original network
// we represent forward edge i as 2 * i and backedge as 2*i + 1
// thus forward and backedge of indices i1, i2 relate in this way:
// i1 ^ 1 = i2, i2 ^ 1 = i1
struct Dinic {
    i64 n, s, t;
    vector<vector<i64>> adj;  // maps vertex to edge indices
    vector<Edge> edges;
    // performance optimization to push flow possibly more than once
    // after each bfs/layer graph build
    vector<i64> cur_edge_ptr;

    void add_edge(i64 u, i64 v, i64 c){
        // set flow at c so effective cap of back edge starts at 0
        Edge forward(u, v, c, 0), backward(v, u, c, c);

        adj[u].emplace_back(edges.size());
        edges.emplace_back(forward);
        adj[v].emplace_back(edges.size());
        edges.emplace_back(backward);
    }

    Dinic(const i64 n, i64 s, i64 t) : n(n), s(s), t(t){
        adj.resize(n);
        cur_edge_ptr.assign(n, 0);
    }

    Dinic(const vector<vector<pair<i64, i64>>> g, i64 s, i64 t)
        : n(g.size()), s(s), t(t) {
        adj.resize(n);
        cur_edge_ptr.assign(n, 0);
        for (i64 u = 0; u < n; u++){
            for (auto[c, v]: g[u]){
                add_edge(u, v, c);
            }
        }
    }

    // level vector --> implicit layer graph (by takings edges where d increases by 1)
    // pass by ref to optimize copies
    void layer_graph(vector<i64>& level, i64 lim = 1){
        fill(level.begin(), level.end(), INF);
        queue<pair<i64, i64>> q;
        q.emplace(s, 0);
        while (!q.empty()){
            auto[u, l] = q.front();
            q.pop();
            if (level[u] != INF) continue;
            level[u] = l;
            for (i64 id: adj[u]){
                Edge e = edges[id];  // u -> v
                if (e.cap() < lim) continue;  // edge does not exist
                i64 v = e.v;
                if (level[v] == INF){
                    q.emplace(v, l + 1);
                }
            }
        }
    }

    // push_flow on layer dag of residual graph 
    bool can_push_flow(i64 u, vector<i64>& level, i64 flow){
        if (flow == 0) {
            return false;
        }
        if (u == t){
            return true;  // already at sink
        }
        for (; cur_edge_ptr[u] < (i64)adj[u].size(); cur_edge_ptr[u]++){
            i64 id = adj[u][cur_edge_ptr[u]];
            // edges[id] is forward edge (relative to u): u -> v
            i64 v = edges[id].v;
            if (level[v] != level[u] + 1) continue;  // not dag edge
            if (edges[id].cap() < flow) continue;
            if (can_push_flow(v, level, flow)) {
                edges[id].f += flow;
                edges[id ^ 1].f -= flow;
                return true;
            }
        }
        return false;
    }

    i64 maxflow(){
        i64 maxFlow = 0;
        vector<i64> level(n);
        for (i64 lim = INF; lim >= 1; ){
            layer_graph(level, lim);
            if (level[t] == INF) {
                lim >>= 1;
                continue;
            }  // no more augmenting paths
            // can't assume anyone is blocked (reuse block vector), since we might try to unblock by undoing flow
            fill(all(cur_edge_ptr), 0);  // reset edge ptr
            while (can_push_flow(s, level, lim)){
                maxFlow += lim;
            }
        }
        return maxFlow;
    }
};

void solve(){
    i64 n;
    cin >> n;
    vector<vector<i64>> a(n, vector<i64>(n));
    i64 T = 0;
    i64 exceeding = 0, zeroes = 0;

    // (id, amount)
    vector<vector<pair<i64, i64>>> exceeding_per_col(n), exceeding_per_row(n);
    // id
    vector<vector<i64>> zeroes_per_row(n), zeroes_per_col(n);
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            cin >> a[i][j];
            T += max(a[i][j] - 1, (i64)0);
            exceeding += a[i][j] > 1;
            zeroes += a[i][j] == 0;
        }
    }
    // cerr << "exceeding=" << exceeding << " zeroes=" << zeroes << endl;

    // indexes
    i64 _cur_ex = 1, _cur_z = exceeding + 1;
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            if (a[i][j] > 1){
                // 1-indexed
                exceeding_per_row[i].emplace_back(_cur_ex, a[i][j] - 1);
                exceeding_per_col[j].emplace_back(_cur_ex, a[i][j] - 1);
                ++_cur_ex;
            } else if (a[i][j] == 0){
                zeroes_per_row[i].emplace_back(_cur_z);
                zeroes_per_col[j].emplace_back(_cur_z);
                ++_cur_z;
            }
        }
    }
    // printgraph("exceeding_per_row=", exceeding_per_row);
    // printgraph("exceeding_per_col=", exceeding_per_col);
    // printgraph("zeroes_per_row=", zeroes_per_row);
    // printgraph("zeroes_per_col=", zeroes_per_col);
    // T = total of stones to move
    // s = 0
    // then we have :exceeding: vertices for each element a[i][j] > 1
    // then :zeroes: vertices for each element a[i][j] = 0
    // then n vertices (one for each row)
    // then n vertices (one for each col)
    Dinic network(2 + exceeding + zeroes + 2 * n, 0, exceeding + zeroes + 2 * n + 1);
    const i64 BASE_ROW = exceeding + zeroes + 1,
            BASE_COL = exceeding + zeroes + n + 1;

    // s -> (i,j) exceeding of capacity a[i][j] - 1
    // (i,j) zero -> t with capacity 1 since it can only receive one element
    const i64 s = 0, t = exceeding + zeroes + 1 + 2 * n;
    for (i64 i = 0; i < n; i++){
        for (auto[idx, c]: exceeding_per_row[i]){
            network.add_edge(s, idx, c);
        }
        for (i64 idx: zeroes_per_row[i]){
            network.add_edge(idx, t, 1);
        }
    }
    // cerr << "ok first part" << endl;
    // (i, j) exceeding -> row i and col j
    // row i and col j -> (i, j) zero
    for (i64 i = 0; i < n; i++){
        for (auto[idx, _]: exceeding_per_row[i]){
            network.add_edge(idx, BASE_ROW + i, INF);
        }
        for (auto[idx, _]: exceeding_per_col[i]){
            network.add_edge(idx, BASE_COL + i, INF);
        }
        for (i64 idx: zeroes_per_row[i]){
            network.add_edge(BASE_ROW + i, idx, INF);
        }
        for (i64 idx: zeroes_per_col[i]){
            network.add_edge(BASE_COL + i, idx, INF);
        }
    }
    // cerr << "ok full build" << endl;
    i64 F = network.maxflow();
    i64 ANS = F + 2 * (T - F);
    cout << ANS << endl;
}
 
signed main(){
	fastio;
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
