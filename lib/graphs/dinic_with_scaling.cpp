// Tested on CSES - Police Chases
#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t

// Same as dinic but with edge scaling
// Complexity is O(VE log U) where U = max edge capacity
// WE ONLY INCLUDE WHAT CHANGED
const i64 INF = (i64)(1ll << 60);  // best to use a power of 2

// level vector --> implicit layer graph (by takings edges where d increases by 1)
// -----------------------------------
// NOTE: when using dinic with scaling for mincut, do layer graph with default lim of 1
// -----------------------------------
void layer_graph(i64 lim = 1){
    fill(level.begin(), level.end(), INF);
    level[s] = 0;
    q.emplace(s);
    while (!q.empty()){
        i64 u = q.front();
        q.pop();
        for (i64 id: adj[u]){
            const Edge& e = edges[id];  // u -> v
            if (e.cap() < lim) continue;  // edge does not exist
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
bool can_push_flow(i64 u, vector<i64>& level, i64 flow){
    if (u == t){
        return true;  // already at sink
    }
    for (; cur_edge_ptr[u] < (i64)adj[u].size(); cur_edge_ptr[u]++){
        i64 id = adj[u][cur_edge_ptr[u]];
        // edges[id] is forward edge (relative to u): u -> v
        i64 v = edges[id].v;
        if (level[v] != level[u] + 1) continue;  // not dag edge
        if (edges[id].cap() < flow) continue;  // edge does not exist
        i64 pushed = can_push_flow(v, level, flow);
        if (pushed){
            edges[id].f += flow;
            edges[id ^ 1].f -= flow;
            return true;
        }
    }
    return false;
}

i64 maxflow(){
    for (i64 lim = INF; lim >= 1; ){
        layer_graph(lim);
        if (level[t] == INF) {
            lim >>= 1;
            continue;
        }  // no more augmenting paths
        // can't assume anyone is blocked (reuse block vector), since we might try to unblock by undoing flow
        fill(cur_edge_ptr.begin(), cur_edge_ptr.end(), 0);  // reset edge ptr
        while (can_push_flow(s, level, lim)) {}
    }
    i64 maxFlow = 0;
    for (i64 id: adj[s]) {
        maxFlow += edges[id].f;
    }
    return maxFlow;
}