#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>
/*
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, typename Cmp_Fn = std::less<T>>
using iset = __gnu_pbds::tree<
    T,
    __gnu_pbds::null_type,
    Cmp_Fn,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
>;
//*/
using namespace std;

using i32 = int32_t;
using i64 = int64_t;
using str = string;
using pii = pair<i64, i64>;
#define vt vector
using vi = vt<i64>;

#define iab(i, a, b) for (i64 i = (a); i < (b); i++)
#define iba(i, a, b) for (i64 i = (b-1); i >= (a); i--)
#define i0n(i, n) iab(i, 0, n)
#define in0(i, n) iba(i, 0, n)
#define rep(k) i0n(_, k)

template <typename ...T> void pr(T ...t) { ((cout << t << ' '), ...); }
template <typename ...T> void prn(T ...t) { pr(t...); cout << '\n'; }
template <typename ...T> void re(T &...t) { (cin >> ... >> t); }

#define sz(X) ((i64)X.size())
#define all(X) X.begin(),X.end()
#define lla(X) X.rbegin(),X.rend()
#define each(x, X) for (auto x : X)
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << " ";} cout << endl;

#define inp(T, ids...) T ids; re(ids)
#define inpv(T, id, n) vt<T> id(n); each(&x, id) re(x)

void solve() {
    inp(i64, n);
    inpv(i64, a, 2*n);
    i0n(i, 2*n) a[i]--;
    vi pos(n, -1);
    vi dp(2*n+1);
    vi cost(2*n+1, 1e18);
    cost[2*n] = 0;
    for (i64 i = 2*n-1; i >= 0; i--) {
        if (pos[a[i]] == -1) {
            pos[a[i]] = i;
            dp[i] = dp[i+1];
            cost[i] = cost[i+1];
        } else {
            dp[i] = dp[pos[a[i]] + 1] + 1;
            if (dp[i+1] > dp[i]) {
                dp[i] = dp[i+1];
                cost[i] = cost[i+1];
            } else if (dp[i+1] == dp[i]) {
                cost[i] = min(
                    cost[pos[a[i]]+1] + pos[a[i]] - i,
                    cost[i+1]
                );
            } else {
                cost[i] = cost[pos[a[i]]+1] + pos[a[i]] - i;
            }
        }
    }
    // printmsg("", dp.begin(), dp.end());
    // printmsg("", cost.begin(), cost.end());
    cout << dp[0] << " " << cost[0] << endl;
}

i32 main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // i32 t; cin >> t; while (t--)
    solve();
}