#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vvi vector<vector<int>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define int long long

const int INF = 2e18;

// if there are multiples paths from s to v with distances
// d1 > ... > d_n, and they are visited in that order, then there will be suboptimal
// states in the priority_queue
void dijkstra(vvpi &adj, int dis[], int s)
{
    for (int i = 0; i < (int)adj.size(); i++) dis[i] = INF;

    priority_queue< pii, vector<pii>, greater<pii> > pq;
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

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vvpi adj(n);
    int a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        adj[a - 1].emplace_back(c, b - 1);
    }
    int dis[n];
    dijkstra(adj, dis, 0);
    for (int i = 0; i < n; i++)
    {
        cout << dis[i] << ' ';
    }
}