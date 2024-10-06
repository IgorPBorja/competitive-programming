//#include <bits/stdc++.h>
//#define USACO
#define TESTCASES

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

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

vector<vector<i64>> adj;
vector<i64> colors;
vector<i64> red, blue;

void color2(i64 u, i64 c){
    colors[u] = c;
    if (c == 0){
        red.emplace_back(u + 1);
    } else {
        blue.emplace_back(u + 1);
    }
    for (i64 v: adj[u]){
        if (colors[v] == -1){
            color2(v, 1 - c);
        }
    }
}

void solve(){
    i64 n, m, x, y;
    cin >> n >> m;
    adj.assign(n, vector<i64>(0));
    colors.assign(n, -1);
    red.resize(0);
    blue.resize(0);

    for (i64 i = 0; i < m; i++){
        cin >> x >> y;
        --x; --y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    color2(0, 0);
    if (red.size() < blue.size()){
        cout << red.size() << endl;
        for (i64 x: red){
            cout << x << " ";
        }
    } else {
        cout << blue.size() << endl;
        for (i64 x: blue){
            cout << x << " ";
        }
    }
    cout << endl;
}

int main(){
#ifdef TESTCASES
    i64 t;
    cin >> t;
    while (t--){
        solve();
    }
#else
    solve();
#endif
}
