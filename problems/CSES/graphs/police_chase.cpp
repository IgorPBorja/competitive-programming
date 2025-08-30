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
    i64 u, v;
    i64 c, f;
    i64 other(i64 x){
        return (x == u ? v : u);
    }
    i64 cap_from(i64 x){
        if (x == u){
            return c - f;
        } else {
            return f;
        }
    }

    void add_flow(i64 from, i64 dF){
        if (from == u) { // consume flow
            f += dF;
        } else { // undo flow
            f -= dF;
        }
    }
    Edge(i64 from, i64 to, i64 cap) : u(from), v(to), c(cap), f(0) {}
};

struct Dinic {
    i64 n, s, t;
    vector<vector<Edge*>> adj;  // [cap, to] pairs

    void add_edge(i64 u, i64 v, i64 c){
        // must be heap-allocated, or else will disappear when leaving function
        Edge* e = new Edge(u, v, c);   
        adj[u].emplace_back(e);
        adj[v].emplace_back(e);
    }

    Dinic(const vector<vector<pair<i64, i64>>> g, i64 s, i64 t)
        : n(g.size()), s(s), t(t) {
        adj.resize(n);
        for (i64 u = 0; u < n; u++){
            for (auto[c, v]: g[u]){
                add_edge(u, v, c);
            }
        }
    }

    // dag adj list, level vector
    pair<vector<vector<Edge*>>, vector<i64>> make_dag(){
        vector<vector<Edge*>> dag(n);
        vector<i64> level(n, INF);
        queue<i64> q;
        q.emplace(s);
        level[s] = 0;
        vector<i64> vis(n, false);
        while (!q.empty()){
            i64 u = q.front();
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (Edge* e: adj[u]){
                if (e->cap_from(u) == 0) continue;  // edge does not exist
                i64 v = e->other(u);
                if (!vis[v]){
                    level[v] = level[u] + 1;
                    dag[u].emplace_back(e);
                    q.emplace(v);
                }
            }
        }
        return {dag, level};
    }

    // push_flow on layer dag of residual graph 
    i64 push_flow(i64 u, vector<i64>& blocked, vector<i64>& level, i64 dF = INF){
        if (u == t){
            return dF;  // already at sink
        }
        bool all_neighbors_blocked = true;
        i64 pushedF = 0;
        for (Edge* e: adj[u]){
            if (dF == 0) break;
            i64 v = e->other(u);
            if (level[v] != level[u] + 1) continue;  // not dag edge
            if (e->cap_from(u) == 0 || blocked[v]) continue;
            
            // NOTE: this push_flow might block v!
            i64 delta = push_flow(v, blocked, level, min(e->cap_from(u), dF));
            e->add_flow(u, delta);
            dF -= delta;
            pushedF += delta;

            if (e->cap_from(u) > 0 && !blocked[v]){  // still valid after pushing
                all_neighbors_blocked = false;
            }
        }
        if (all_neighbors_blocked) blocked[u] = true;
        return pushedF;
    }

    i64 maxflow(){
        while (true){
            auto[dag, level] = make_dag();
            // can't assume anyone is blocked, since we might try to unblock by undoing flow
            if (level[t] == INF) break;  // no more augmenting paths
            vector<i64> blocked(n, false);  // indicates that vertex is blocked: can't push flow from it
            push_flow(s, blocked, level);
        }
        i64 maxFlow = 0;
        for (Edge* e: adj[s]){
            if (s == e->u){  // is origin vertex: forward edge
                maxFlow += e->f;
            } else {  // backward edge
                maxFlow -= e->f; 
            }
        }
        return maxFlow;
    }

    // assumes dinic was called first
    vector<i64> mincut(){
        auto[_, level] = make_dag();
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
    for (i64 i = 0; i < m; i++){
        i64 u, v;
        cin >> u >> v;  // already 1-indexed
        adj[u].emplace_back(1, v);
        adj[v].emplace_back(1, u);
        edges.emplace_back(u, v);
    }
    adj[0].emplace_back(INF, 1);  // source to start vertex

    Dinic d(adj, 0, n);
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
 