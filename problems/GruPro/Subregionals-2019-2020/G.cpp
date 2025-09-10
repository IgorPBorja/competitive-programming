#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<class T> using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define dbg(x) cerr << #x << " = " << x << endl;
#define int long long
// #define double long double
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(),a.rend()
#define endl "\n"
#define i64 int64_t
const int mod = 1e9 + 7, mod2 = 998244353;
const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };     

int lcm(int a,int b){
    return a/__gcd(a,b)*b;
}

const int maxN = 2e5 + 5,maxK = 501, LOGN =21;
using ld = long double;

const ld INF = 1e9;

// max cost assignment
pair<ld, vector<i64>> hungarian(const vector<vector<ld>>& a){ // a = cost matrix
    if (a.empty()) return {0, {}};
    i64 n = a.size() + 1, m = a[0].size() + 1;
    vector<i64> p(m), ans(n - 1);
    vector<ld> u(n), v(m);
    vector<bool> done(m + 1);
    for (i64 i = 1; i < n; i++){
        p[0] = i;  // p is i64
        i64 j0 = 0;
        vector<ld> dist(m, INF);
        vector<i64> pre(m, -1);
        do {
            done[j0] = true;
            i64 i0 = p[j0], j1;
            ld delta = INF;  // delta is ld
            for (i64 j = 1; j < m; j++){
                if (!done[j]){
                    ld cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < dist[j]) dist[j] = cur, pre[j] = j0;  // pre is i64
                    if (dist[j] < delta) delta = dist[j], j1 = j;
                }
            }
            for (i64 j = 0; j < m; j++){
                if (done[j]) u[p[j]] += delta, v[j] -= delta;  // u, v are ld
                else dist[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);
        while (j0){
            i64 j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    for (i64 j = 1; j < m; j++) if (p[j]) ans[p[j] - 1] = j - 1;  // ans is i64
    return {-v[0], ans};
}

void solve(){
    i64 n;
    cin >> n;
    vector<vector<ld>> a(n, vector<ld>(n));
    i64 x;
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            cin >> x;
            a[i][j] = logl((ld)1.0 / (ld)x);  // log(1/x) = -log(x), using logl for more precision
        }
    }
    auto[_, p] = hungarian(a);
    vector<i64> invp(n);
    for (i64 i = 0; i < n; i++) {
        invp[p[i]] = i;
    }
    for (i64 x: invp){
        cout << x + 1 << " ";
    }
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
