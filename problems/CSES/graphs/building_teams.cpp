#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define vi vector<int>

/*find component components. Let C(G) be the number of component components and 
component[] be a list of then
if C(G) < 2:
    impossible
else:
    assign 1 + (i mod 2) for the nodes in component i
*/

bool bfs_color(vvi& adj, int s, vi& coloring){
    int curr_color = 1;
    queue<int> q;
    q.emplace(s);
    coloring[s] = 1;
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int v : adj[u]){
            if (coloring[u] == coloring[v]){
                // conflict
                return false;
            } else {
                if (coloring[v] == -1){ // not visited
                    coloring[v] = 3 - coloring[u]; // switch 1->2 or 2->1
                    q.emplace(v);
                }
            }
        }
    }
    return true;
}

vi bipartite_coloring(vvi& adj){
    int n = (int)adj.size();
    vi coloring(n, -1);
    for (int i = 0; i < n; i++){
        if (coloring[i] == -1){ // not visited
            bool flag = bfs_color(adj, i, coloring);
            if (!flag){
                return vi(0);
            }
        }
    }
    return coloring;
}

int main(){
    int n, m;
    cin >> n >> m;
    vvi adj(n);
    
    int a,b;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        adj[a - 1].emplace_back(b - 1);
        adj[b - 1].emplace_back(a - 1);
    }
    vi labels = bipartite_coloring(adj);
    if (labels.size() == 0){
        cout << "IMPOSSIBLE";
    } else {
        for (int i = 0; i < n; i++){
            cout << labels[i] << ' ';
        }
    }
}