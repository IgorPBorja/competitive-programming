#include <bits/stdc++.h>
using namespace std;
 
#define i64 int64_t
#define printcap(mat) for (size_t i = 0; i < (mat.size() - 2) / 2; i++){ \
    for(size_t j = 0; j < (mat[i].size() - 2) / 2; j++) { \
        if (mat[i][(mat[i].size() - 2) / 2 + j] < INF / (i64)2) cout << fixed << setw(3) << mat[i][(mat[i].size() - 2) / 2 + j] << " "; \
        else cout << "INF" << " "; \
    } \
    cout << endl; \
}
 
const i64 INF = 2e18;
 
void shortest_paths(
    vector<vector<i64>>& g, vector<vector<i64>>& capacity,
    vector<vector<i64>>& cost, i64 s, vector<i64>& dist, vector<i64>& parent
) {
    const i64 n = g.size();
    dist.assign(n, INF);
    dist[s] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(s);
    parent.assign(n, -1);
 
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : g[u]) {
            if (capacity[u][v] > 0 && dist[v] > dist[u] + cost[u][v]) {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}
 
 
// MCMF on complete bipartite graph with unit capacities
pair<i64, set<pair<i64, i64>>> mcmf_bipartite_unit(
    vector<vector<i64>>& g,
    vector<vector<i64>>& cost
){
    const i64 n = g.size(), k = (g.size() - 2) / 2;
    const i64 s = n - 2, t = n - 1;
    vector<i64> d(n), p(n);
 
 
    vector<vector<i64>> capacity(n, vector<i64>(n));
    for (i64 i = 0; i < k; i++){
        for (i64 j = 0; j < k; j++){
            capacity[i][k + j] = 1;
            // taking one unit of flow from v to u undoes taking one unit of flow
            // from u to v, which costs cost[u][v]
            // capacity[v][u] starts at 0 and increases as stuffs gets to v from u
            // (to allow for rollbacks)
            cost[k + j][i] = -cost[i][k + j];
        }
        // source vertex 2 * k
        cost[2 * k][i] = 0;
        // element in side A can only push unit of flow to 1 member of side B
        capacity[2 * k][i] = 1;
        capacity[2 * k][k + i] = 1;
        // sink vertex 2 * k + 1
        cost[k + i][2 * k + 1] = 0;
        // element in side B can only receive unit of flow from 1 member of side A
        capacity[k + i][2 * k + 1] = 1;
    }
 
    i64 total_cost = 0;
    i64 total_flow = 0;
    set<pair<i64, i64>> assignments;
    
 
    while (true){
        // try to run shortest path
        shortest_paths(g, capacity, cost, s, d, p);
        if (d[t] == INF) break;
        total_cost += d[t];
 
        // apply flow
        i64 cur = t;
        // auto strnode = [k](i64 node){
        //     if (0 <= node && node < k){
        //         return "A-" + to_string(node + 1);
        //     } else if (k <= node && node < 2 * k){
        //         return "B-" + to_string(node - k + 1);
        //     } else if (node == 2 * k) {
        //         return string("START");
        //     } else {
        //         return string("END");
        //     }
        // };
        while (cur != s){
            // forward edge p[cur] -> cur
            --capacity[p[cur]][cur];
            ++capacity[cur][p[cur]];
            // cerr << "p[cur]=" << strnode(p[cur]) << " cur=" << strnode(cur) << " delta cost=" << cost[p[cur]][cur] << endl;
 
            i64 i = min(p[cur], cur), j = max(p[cur], cur) - k;
            if (0 <= i && i < k && 0 <= j && j < k){
                // i is in side A, j is in side B of bipartition
                // cerr << "i=" << i << " j=" << j << endl;
                if (i == p[cur]) {
                    assignments.emplace(i, j);
                }
                else {
                    assignments.erase(make_pair(i, j));
                }
            }
            cur = p[cur];
        }
        ++total_flow;
        // printcap(capacity);
    }
 
    return { total_cost, assignments };
}
 
int main(){
    // bipartite complete graph of employees and tasks and unit capacities, with a source and sink with infinite capacity
 
    i64 n;
    cin >> n;
    vector<vector<i64>> cost(2 * n + 2, vector<i64>(2 * n + 2));
    vector<vector<i64>> g(2 * n + 2);
    for (i64 i = 0; i < n; i++){
        g[2 * n].emplace_back(i);
        for (i64 j = 0; j < n; j++){
            g[i].emplace_back(n + j);
            g[n + j].emplace_back(i);
        }
        g[n + i].emplace_back(2 * n + 1);
    }
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            cin >> cost[i][n + j];
        }
    }
    auto[total_cost, assignments] = mcmf_bipartite_unit(g, cost);
 
    cout << total_cost << endl;
    for (auto[emp, task]: assignments){
        cout << emp + 1 << " " << task + 1 << endl;
    }
}