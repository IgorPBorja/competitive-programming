#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<class T> using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define dbg(x) cerr << #x << " = " << x << endl;
#define int long long
#define double long double
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

const int maxN = 2e5 + 5,maxK = 501, INF = 1e15, LOGN =21;

void solve(){
    i64 n, c, t;
    cin >> n >> c >> t;
    vector<i64> p(n);
    for (i64 i = 0; i < n; i++){
        cin >> p[i];
    }

    auto check = [&p, c, t](i64 dt){
        i64 idx = 0;
        const i64 n = p.size();
        // linear time amortized?
        for (i64 j = 0; j < c; j++){
            i64 acc = 0;
            while (idx < n && p[idx] + acc <= dt * t){
                acc += p[idx++];
            }
        }
        return idx == n;
    };

    // at worst C = 1, T = 1 and N = 1e5 with P[i]=1e4
    // so takes 1e9 time
    i64 l = 1, r = 1e9;
    i64 ans = 1e9;
    while (l <= r){
        const i64 m = l + (r - l) / 2;
        if (check(m)){
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << ans << endl;
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
