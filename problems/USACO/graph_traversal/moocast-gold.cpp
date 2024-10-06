//#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

#define USACO
#ifdef USACO
    ofstream fout("moocast.out");
    ifstream fin("moocast.in");
    #define cin fin
    #define cout fout
#endif

#define i64 int64_t

template<typename T>
ostream& operator<<(ostream& os, vector<T> v){
    for (T x: v){
        os << x << " ";
    }
    return os;
}

vector<vector<pair<i64, i64>>> adj;
vector<pair<i64, i64>> pts;

bool is_totally_conn(i64 u, i64 max_cost){
    queue<i64> q;
    vector<bool> vis(adj.size(), false);
    q.emplace(u);
    while (!q.empty()){
        i64 v = q.front();
        q.pop();
        if (vis[v]){
            continue;
        }
        vis[v] = true;
        for (auto[d, w]: adj[v]){
            if (!vis[w] && d <= max_cost){
                q.emplace(w);
            }
        }
    }

    bool ok = true;
    for (bool status: vis){
        ok &= status;
    }
    return ok;
}

i64 L2(pair<i64, i64> p1, pair<i64, i64> p2){
    return (p2.first - p1.first) * (p2.first - p1.first)
        + (p2.second - p1.second) * (p2.second - p1.second);
}

signed main(){
    i64 n;
    cin >> n;
    pts.resize(n);
    adj.resize(n);

    for (i64 i = 0; i < n; i++){
        cin >> pts[i].first >> pts[i].second;
    }

    for (i64 i = 0; i < n; i++){
        for (i64 j = i + 1; j < n; j++){
            i64 d = L2(pts[i], pts[j]);
            adj[i].emplace_back(d, j);
            adj[j].emplace_back(d, i);
        }
    }

    // max individual dist is 25000^2 + 25000^2 = 2 * 25000^2 = 1.2e3 * 1e3 = 1e6
    // times n edges -> 1e9
    i64 l = 0, r = 4e9, ans = 4e9;
    while (l <= r){
        i64 mid = l + (r - l) / (i64)2;
        bool ok = is_totally_conn(0, mid);
        if (ok){
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
}
