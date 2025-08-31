#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t

// toposort with bfs, returns the lexicographically smallest topological order
// Runs in O(n log n) because of sorting
// Returns boolean indicating if topo order exists, and the order in case it does
pair<bool, vector<i64>> lexicographical_toposort(const vector<vector<i64>>& dag){
    const i64 n = dag.size();
    // dependencies_met[i]: how many j such that j->i
    // have received their order number
    vector<i64> dependencies_met(n, 0),
                in_degree(n, 0),
                order(n, -1);
    for (i64 u = 0; u < n; u++){
        for (i64 v: dag[u]){
            ++in_degree[v];
        }
    }
    priority_queue<i64, vector<i64>, greater<i64>> q;
    // min pq guarentees lexicographical order and topo order
    // by only pushing when all dependencies are met
    for (i64 u = 0; u < n; u++){
        if (!in_degree[u]) q.emplace(u);
    }
    i64 c = 0;
    while (!q.empty()){
        i64 u = q.top();
        order[u] = c++;
        q.pop();
        for (i64 v: dag[u]){
            ++dependencies_met[v];
            if (dependencies_met[v] == in_degree[v]){
                q.emplace(v);
            }
        }
    }
    for (i64 u = 0; u < n; u++){
        // circular dependencies exist
        if (order[u] == -1) return {false, {}};
    }
    return {true, order};
}