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

const i64 INF = (i64)2e18;

void solve(){
    i64 n, k, x;
    cin >> n >> k >> x;
    vector<i64> s(n), e(n);
    for (i64 i = 0; i < n; i++){
        cin >> s[i] >> e[i];
    }
    
    // dp[i] = max health of queen starting at i with 0 energy
    vector<i64> dp(n + 1);
    dp[n] = 0;  // he starts with 0 energy
    
    for (i64 i = n - 1; i >= 0; i--){
        dp[i] = -INF;
        // try to defeat s[i] space mutants, than gain e[i] energy and go to the next one
        // remainder is e[i] - s[i] extra
        dp[i] = max(dp[i], dp[i + 1] + e[i] - s[i]);
        
        
        // try to take X guards then go to wormhole
        // remainder is -X
        dp[i] = max(dp[i], dp[min(i + k, n)] - x);
    }
    // printmsg("dp=", dp.begin(), dp.end());
    cout << max(dp[0], (i64)0) << endl;
}

signed main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(t--)solve();
}
