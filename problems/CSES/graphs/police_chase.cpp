// #define TESTCASES
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t

/*
Dinic (overview):
// make residual graph (edges and backedges)
// then on each iteration
// do bfs to make layer graph
// do dfs to find blocking flow
*/

const i64 INF = (i64)2e18;
struct Edge {
    i64 u, v, c, f;
    i64 cap() const { return c - f; }
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
    // performance optimization to avoid looking at blocked nodes
    vector<i64> blocked;
    vector<i64> level;
    queue<i64> q;

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
        level.resize(n);
        cur_edge_ptr.assign(n, 0);
        blocked.assign(n, false);
        edges.reserve(2 * n);
    }

    Dinic(const vector<vector<pair<i64, i64>>> g, i64 s, i64 t)
        : n(g.size()), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        cur_edge_ptr.assign(n, 0);
        blocked.assign(n, false);
        edges.reserve(2 * n);
        for (i64 u = 0; u < n; u++){
            for (auto[c, v]: g[u]){
                add_edge(u, v, c);
            }
        }
    }

    // level vector --> implicit layer graph (by takings edges where d increases by 1)
    // pass by ref to optimize copies
    void layer_graph(){
        fill(level.begin(), level.end(), INF);
        level[s] = 0;
        q.emplace(s);
        while (!q.empty()){
            i64 u = q.front();
            q.pop();
            for (i64 id: adj[u]){
                const Edge& e = edges[id];  // u -> v
                if (e.cap() == 0) continue;  // edge does not exist
                i64 v = e.v;
                if (level[v] == INF){
                    level[v] = level[u] + 1;
                    q.emplace(v);
                }
            }
        }
        while (!q.empty()) q.pop();
    }

    // push_flow on layer dag of residual graph 
    i64 push_flow(i64 u, vector<i64>& blocked, vector<i64>& level, i64 dF){
        if (u == t){
            return dF;  // already at sink
        }
        bool all_neighbors_blocked = true;  // performance optimization
        i64 total_pushed = 0;
        for (; cur_edge_ptr[u] < (i64)adj[u].size() && dF > 0; cur_edge_ptr[u]++){
            i64 id = adj[u][cur_edge_ptr[u]];
            // edges[id] is forward edge (relative to u): u -> v
            i64 v = edges[id].v;
            if (level[v] != level[u] + 1) continue;  // not dag edge
            if (edges[id].cap() == 0 || blocked[v]) continue;  // edge does not exist
            i64 pushed = push_flow(v, blocked, level, min(edges[id].cap(), dF));
            edges[id].f += pushed;
            edges[id ^ 1].f -= pushed;
            total_pushed += pushed;
            dF -= pushed;

            if (edges[id].cap() > 0 && !blocked[v]) {  // edge still valid
                all_neighbors_blocked = false;
            }
        }
        if (all_neighbors_blocked) blocked[u] = true;
        return total_pushed;
    }

    i64 maxflow(){
        while (true){
            layer_graph();
            if (level[t] == INF) {
                break;
            }  // no more augmenting paths
            // can't assume anyone is blocked (reuse block vector), since we might try to unblock by undoing flow
            fill(cur_edge_ptr.begin(), cur_edge_ptr.end(), 0);  // reset edge ptr
            fill(blocked.begin(), blocked.end(), false);  // reset blocked
            while (push_flow(s, blocked, level, INF)) {}
        }
        i64 maxFlow = 0;
        for (i64 id: adj[s]) {
            maxFlow += edges[id].f;
        }
        return maxFlow;
    }

    // assumes dinic was called first
    vector<i64> mincut(){
        layer_graph();
        vector<i64> partition_num(n);
        for (i64 u = 0; u < n; u++){
            if (level[u] < INF){
                partition_num[u] = 0;
            } else {
                partition_num[u] = 1;
            }
        }
        return partition_num;
    }
};

signed main(){
	fastio;
    i64 n, m;
    cin >> n >> m;

    vector<vector<pair<i64, i64>>> adj(n + 1);
    vector<pair<i64, i64>> edges;
    Dinic d(n + 1, 0, n);
    for (i64 i = 0; i < m; i++){
        i64 u, v;
        cin >> u >> v;  // already 1-indexed
        d.add_edge(u, v, 1);
        d.add_edge(v, u, 1);
        edges.emplace_back(u, v);
    }
    d.add_edge(0, 1, INF);  // source to start vertex

    i64 maxflow = d.maxflow();
    i64 mincut_value = maxflow;
    vector<i64> mincut_partition = d.mincut();
    vector<pair<i64, i64>> cut_edges;
    for (auto[u, v]: edges){
        // edges are undirected so if u,v are in different partitions then
        // there is the edge from the one on partition 0 to the on on partition 1
        if (mincut_partition[u] == 0 && mincut_partition[v] == 1){
            cut_edges.emplace_back(u, v);
        } else if (mincut_partition[u] == 1 && mincut_partition[v] == 0){
            cut_edges.emplace_back(v, u);
        }
    }

    cout << mincut_value << endl;
    for (auto[u, v]: cut_edges) cout << u << " " << v << endl;
}
 