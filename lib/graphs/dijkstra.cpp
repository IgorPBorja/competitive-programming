#include <bits/stdc++.h>
using namespace std;
 
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