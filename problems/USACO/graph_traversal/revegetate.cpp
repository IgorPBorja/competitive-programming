//#include <bits/stdc++.h>
#define USACO
//#define TESTCASES
#define eb emplace_back
#define pb push_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

#ifdef USACO
    ofstream fout("revegetate.out");
    ifstream fin("revegetate.in");
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

vector<vector<i64>> same_adj, diff_adj;
vector<i64> colors;
bool ok = true;

void dfs(i64 u, i64 c){
    colors[u] = c;
    for (i64 v: same_adj[u]){
        if (colors[v] == 1 - colors[u]){
            ok = false;
        } else if (colors[v] == -1){
            dfs(v, c);
        }
    }
    for (i64 v: diff_adj[u]){
        if (colors[v] == colors[u]){
            ok = false;
        } else if (colors[v] == -1){
            dfs(v, 1 - c);
        }
    }
}

void solve(){
    cout << "starting" << endl;
    i64 n, m, x, y;
    string mode;
    cin >> n >> m;
    same_adj.resize(n);
    diff_adj.resize(n);
    colors.assign(n, -1);

    for (i64 i = 0; i < m; i++){
        cin >> mode >> x >> y;
        --x; --y;
        if (mode == "S"){
            same_adj[x].eb(y);
            same_adj[y].eb(x);
        } else {
            diff_adj[x].eb(y);
            diff_adj[y].eb(x);
        }
    }
    cout << "input ok" << endl;
    
    i64 total = 0;
    for (i64 i = 0; i < n; i++){
        if (colors[i] == -1){
            dfs(i, 0);
            ++total;
        }
    }

    if (!ok){
        cout << 0 << endl;
    } else {
        cout << '1';
        for (i64 i = 0; i < total; i++){
            cout << '0';
        }
        cout << endl;
    }
}

signed main(){
    fastio;
#ifdef TESTCASES
    int t;
    cin >> t;
    while (t--){
        solve();
    }
#else
    solve();
#endif
}
