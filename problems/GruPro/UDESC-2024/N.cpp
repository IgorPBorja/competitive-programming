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
    // x range is 0..N-1, y range is N..N+M-1
    i64 n, m, q;
    cin >> n >> m >> q;
    
    vector<i64> ok_x(n, false), ok_y(m, false);
    
    vector<i64> xs, ys;

    for (i64 i = 0; i < q; i++){
        i64 mode, xi, yi, xf, yf;
        cin >> mode;
        cin >> xi >> yi;
        --xi; --yi;
        if (mode == 1){
            xs.emplace_back(xi);
            ys.emplace_back(yi);
            ok_x[xi] = true;
            ok_y[yi] = true;
        }
        else {
            cin >> xf >> yf;
            --xf; --yf;
            bool res = false;
            if (ok_x[xf]){
                // line at xi, any col
                res |= ok_x[xi] && !ys.empty();
                // col at yi
                res |= ok_y[yi];
            }
            if (ok_y[yf]){
                // col at yi, any line
                res |= ok_y[yi] && !xs.empty();
                // line at xi
                res |= ok_x[xi];
            }
            cout << (res ? "SIM" : "NAO") << endl;
        }
    }
    
}


signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}



