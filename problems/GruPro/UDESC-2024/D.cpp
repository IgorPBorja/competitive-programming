// #define testcases
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define printmsg(msg, first, last) \
    cout << msg; \
    for (auto it = first; it != last; it++) { \
        cout << *it << " "; \
    } \
    cout << endl
    
#define printmat(name, M) \
    for (size_t i = 0; i < M.size(); i++){ \
        cout << name << "[" << i << "]="; \
        for (size_t j = 0; j < M[i].size(); j++){ \
            cout << M[i][j] << " "; \
        } \
        cout << endl; \
    } \
    cout << endl

#define printgraph(msg, G) cout << msg << endl; \
    for (i64 u = 0; u < G.size(); u++) { \
        cout << "G[" << u << "]="; \
        for (i64 v: G[u]){ \
            cout << v << " "; \
        } \
        cout << endl; \
    }

template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> p){
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, queue<T> q){
    while (!q.empty()){
        os << q.front() << " ";
        q.pop();
    }
    return os;
}

void solve(){
    i64 n;
    cin >> n;
    i64 h[n];
    for (i64 i =0 ; i <n ; i++)cin >> h[i];
    i64 m = 0;
    for (i64 i = 0; i < n; i++){
        // at i: m - i - 1 > h[i] ==> m - i - i >= h[i] + 1
        m = max(m, h[i] + i + 2);
    }
    cout << m << endl;
}


signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}



