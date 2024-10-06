#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t
#define USACO

#ifdef USACO
    ofstream fout("moocast.out");
    ifstream fin("moocast.in");
    #define cin fin
    #define cout fout
#endif

i64 dist2(pair<i64, i64> p1, pair<i64, i64> p2){
    return (p1.first - p2.first) * (p1.first - p2.first) 
        + (p1.second - p2.second) * (p1.second - p2.second);
}

i64 dfs(i64 u, vector<vector<i64>>& adj, vector<bool>& vis){
    i64 d = 1;
    vis[u] = true;
    for (i64 v: adj[u]){
        if (!vis[v]){
            d += dfs(v, adj, vis);
        }
    }
    return d;
}

int main(){
    i64 n;
    cin >> n;

    vector<pair<i64, i64>> cows(n);
    vector<vector<i64>> adj(n);
    vector<i64> power(n);
    for(i64 i = 0; i < n; i++){
        i64 x, y, p;
        cin >> x >> y >> p;
        cows[i] = {x, y};
        power[i] = p;
    }


    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i != j && dist2(cows[i], cows[j]) <= power[i] * power[i]){
                adj[i].emplace_back(j);
            }
        }
    }

    i64 mx = 0;
    for (i64 i = 0; i < n; i++){
        vector<bool> vis(n, false);
        mx = max(mx, dfs(i, adj, vis));
    }
    cout << mx << endl;
}
