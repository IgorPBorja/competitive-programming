//#include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>

using namespace std;
#define i64 int64_t
#define USACO

#ifdef USACO
    ofstream fout("fenceplan.out");
    ifstream fin("fenceplan.in");
    #define cin fin
    #define cout fout
#endif

struct Rect{
    i64 min_x, max_x, min_y, max_y;

    Rect(){
        this->min_x = 2e9;
        this->max_x = -2e9;
        this->min_y = 2e9;
        this->max_y = -2e9;
    }

    i64 perimeter(){
        return (i64)2 * ((this->max_x - this->min_x) + (this->max_y - this->min_y));
    }
};

ostream& operator<<(ostream& os, Rect r){
    os << "min_x=" << r.min_x << ", max_x=" << r.max_x << ", min_y=" << r.min_y << ", max_y=" << r.max_y;
    return os;
}

void dfs(i64 u, vector<pair<i64, i64>>& points,
        vector<vector<i64>>& adj, vector<bool>& vis,
        Rect* bbox){
    vis[u] = true;
    bbox->min_x = min(bbox->min_x, points[u].first);
    bbox->max_x = max(bbox->max_x, points[u].first);
    bbox->min_y = min(bbox->min_y, points[u].second);
    bbox->max_y = max(bbox->max_y, points[u].second);
    for (i64 v: adj[u]){
        if (!vis[v]){
            dfs(v, points, adj, vis, bbox);
        }
    }
}

int main(){
    int n, m, x, y;
    cin >> n >> m;

    vector<pair<i64, i64>> points(n);
    vector<vector<i64>> adj(n);
    vector<bool> vis(n, false);

    for (i64 i = 0; i < n; i++){
        cin >> points[i].first >> points[i].second;
    }

    for (i64 i = 0; i < m; i++){
        cin >> x >> y;
        --x; --y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    i64 best_perimeter = 1e18;
    for (i64 i = 0; i < n; i++){
        if (!vis[i]){
            Rect component_rect;
            dfs(i, points, adj, vis, &component_rect);
            //cout << component_rect << endl;
            //cout << "p=" << component_rect.perimeter() << endl;
            best_perimeter = min(best_perimeter, component_rect.perimeter());
        }
    }
    cout << best_perimeter << endl;
}
