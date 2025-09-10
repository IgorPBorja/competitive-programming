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
// /*
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

using ll = long long;
using str = string;
using pii = pair<ll, ll>;
#define vt vector
using vi = vt<ll>;
using vvi = vt<vi>;
template <typename T> using minheap = priority_queue<T, vt<T>, greater<T>>;

#define _OVERLOAD_MACRO_3(_1, _2, _3, name, ...) name
#define _rep3(i, a, b) for (ll i = a; i < (b); i++)
#define _rep2(i, n) _rep3(i, 0, n)
#define _rep1(k) _rep2(_, k)
#define rep(...) _OVERLOAD_MACRO_3(__VA_ARGS__, _rep3, _rep2, _rep1)(__VA_ARGS__)

template <typename ...T> void pr(T ...t) { ((cout << t << ' '), ...); }
template <typename ...T> void prn(T ...t) { pr(t...); cout << '\n'; }
template <typename ...T> void re(T &...t) { (cin >> ... >> t); }

#define sz(X) ((ll)X.size())
#define all(X) X.begin(),X.end()
#define lla(X) X.rbegin(),X.rend()
#define each(x, X) for (auto x : X)

#define inp(T, ids...) T ids; re(ids)
#define inpv(T, id, n) vt<T> id(n); each(&x, id) re(x)

void dfs(ll u, const vector<vector<ll>>& adj, vector<ll>& comp, ll c){
    comp[u] = c;
    for (ll v: adj[u]){
        if (comp[v] == -1){
            dfs(v, adj, comp, c);
        }
    }
}


using T = array<ll, 3>;
void solve() {
    inp(ll, m, n, k);
    vt<array<ll, 3>> a(k);
    rep(i, k) {
        inp(ll, x, y, s);
        a[i] = {x, y, s};
    }

    vi p(k, -1);
    vector<vector<ll>> adj(k);
    rep(i, k) {
        auto [x1, y1, s1]  = a[i];
        rep(j, k) {
            if (i == j) continue;
            auto [x2, y2, s2] = a[j];
            ll xx = (x1-x2)*(x1-x2);
            ll yy = (y1-y2)*(y1-y2);
            ll dd = xx + yy;
            ll ss = (s1+s2)*(s1+s2);
            if (dd <= ss) adj[i].emplace_back(j);
        }
    }
    ll c = 0;
    rep(i, k) {
        if (p[i] == -1){
            dfs(i, adj, p, c);
            ++c;
        }
    }
    using xX_yY = array<ll, 4>;
    vt<xX_yY> g(c, xX_yY({(ll)1e18, (ll)-1e18, (ll)1e18, (ll)-1e18}));
    rep(i, k) {
        auto [x, y, s] = a[i];
        g[p[i]][0] = min(g[p[i]][0], x-s);
        g[p[i]][1] = max(g[p[i]][1], x+s);
        g[p[i]][2] = min(g[p[i]][2], y-s);
        g[p[i]][3] = max(g[p[i]][3], y+s);
    }
    rep(i, c) {
        auto [x, X, y, Y] = g[i];
        if (
            (x <= 0 && X >= m) ||
            (y <= 0 && Y >= n) ||
            (Y >= n && X >= m) ||
            (y <= 0 && x <= 0)
        ) {
            prn("N");
            return;
        }
    }
    prn("S");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // inp(ll, t); rep(t)
    solve();
}
