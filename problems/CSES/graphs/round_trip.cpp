#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define vi vector<int>

// coloring:
// 0: not visited
// 1: visited and in the stack
// 2: visited but not in the stack

int cycle_start = -1;
int cycle_end = -1;
vector<int> parent; // parent[u] stores current parent to u in this DFS call
vector<bool> vis;

bool dfs_cycle(vvi& adj, int u, int p, vector<bool>& vis){
    vis[u] = 1;
    for (int v : adj[u]){
        if (v == p) continue; // skip parent
        if (vis[v]){
            // complete cycle (closing at v)
            cycle_start = v;
            cycle_end = u;
            return true;
        } else if (!vis[v]){
            parent[v] = u;
            if (dfs_cycle(adj, v, parent[v], vis)){
                return true;
            }
        }
    }
    return false;
}

void search_cycle(vvi& adj){
    int n = (int)adj.size();
    vis.assign(n, false);
    parent.assign(n, -1);
    for (int i = 0; i < n; i++){
        if (!vis[i] && dfs_cycle(adj, i, parent[i], vis)){
            // found cycle
            break;
        }
    }
}

int main(){
    int n, m, a, b;
    cin >> n >> m;
    vvi adj(n);
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a - 1].emplace_back(b - 1);
        adj[b - 1].emplace_back(a - 1);
    }

    search_cycle(adj);
    if (cycle_start == -1){
        cout << "IMPOSSIBLE";
    } else {
        vi cyc;
        cyc.emplace_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]){
            cyc.emplace_back(v);
        }
        cyc.emplace_back(cycle_start);
        cout << cyc.size() << '\n';
        for (int u : cyc){
            cout << u + 1 << ' ';
        }
    }
}