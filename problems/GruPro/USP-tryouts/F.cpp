#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <utility>

#define int long long
#define endl '\n'
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
using namespace std;
template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;

const int maxN = 4e5 + 5, mod = 1e9 + 7, mod2 = 998244353, INF=1e18;
vector<pair<int,int>>adj[maxN];

void solve(){
    int n,m,k;
    cin >> n >> m >> k;
    for(int i = 0; i < m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        a--,b--;
        adj[a].emplace_back(b,c);
        adj[b].emplace_back(a,c);
    }
    // verti: 0 ... n-1
    // types: n ... n + k -1
    for(int i = 0; i < n; i++){
        int t;
        cin >> t;
        for(int j = 0; j <t; j++){
            int type, c;
            cin >> type >> c;
            int dummy = n + type - 1;
            adj[i].emplace_back(dummy, c);
            adj[dummy].emplace_back(i,0);
        }
    }
    vector<int>dist(n + k, INF);
    min_pq<pair<int,int>>q;
    q.push({0,0});
    while(!q.empty()){
        auto [d, v] = q.top();
        q.pop();
        if(d >= dist[v])continue;
        dist[v] = d;
        for(auto [u,w]: adj[v]){
            if(dist[u] > dist[v] + w){
                q.emplace(dist[v] + w,u);
            }
        }
    }
    cout << dist[n-1] << endl;
}
signed main(){
	fastio;
    int t = 1;
    // cin >> t;
    while(t--)solve();
}