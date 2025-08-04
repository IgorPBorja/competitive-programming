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
    string s;
    cin >> s >> n;
    vector<vector<i64>> m(26, vector<i64>(26, 0));
    for (i64 i = 0; i < n; i++){
        string u, v;
        cin >> u >> v;
        m[u[0] - 'a'][v[0] - 'a'] = 1;
    }
    bool ok = true;
    for (i64 i = 1; i < s.size(); i++){
        ok &= m[s[i - 1] - 'a'][s[i] - 'a'];
    }
    cout << (ok ? "SIM" : "NAO") << endl;
}


signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}



