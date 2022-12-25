#include <bits/stdc++.h>
using namespace std;
#define INF int(2e9)

void dijkstra(vector<vector<pair<int, int>>>& adj,
            int start,
            int dis[],
            bool vis[])
{
    
    // cost | target
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start));
    dis[start] = 0; vis[start] = true;
    while (!pq.empty())
    {
        auto[_, u] = pq.top();
        pq.pop();
        vis[u] = true;
        for (auto[d2, v]: adj[u]){
            dis[v] = min(dis[v], dis[u] + d2);
            if (!vis[v])
                pq.push(make_pair(d2, v));
        }
    }
}

// example main program
void example(){
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    
    int a, b, w;
    for (int i = 0; i < m; i++){
        cin >> a >> b >> w;
        adj[a - 1].emplace_back(make_pair(w, b - 1));
        adj[b - 1].emplace_back(make_pair(w, a - 1)); // its undirected
    }
    int dis[n];
    for (int i = 0; i < n; i++) dis[i] = INF;
    bool vis[n] = {false};
    
    int start; cin >> start;
    dijkstra(adj, start - 1, dis, vis);
    for (int i = 0; i < n; i++)
        cout << dis[i] << ' ';
}

int main(){
    //example();
}
