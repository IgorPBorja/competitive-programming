#define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 INF = 1e18;

struct MaxSeg {
    vector<i64> seg;
    vector<i64> a;
    i64 n;

    MaxSeg(i64 n) : n(n) {
        seg.assign(4 * n, 0);
        a.resize(n);
    }

    i64 query(i64 l, i64 r){
        if (l > r) return -INF;
        else return _query(l, r, 0, n - 1, 0);
    }

    void update(i64 p, i64 x){
        _update(p, x, 0, n - 1, 0);
    }
private:
    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr){
            return seg[node];
        } else if (r <= tm){
            return _query(l, r, tl, tm, 2 * node + 1);
        } else if (l > tm){
            return _query(l, r, tm + 1, tr, 2 * node + 2);
        } else {
            return max(_query(l, tm, tl, tm, 2 * node + 1), _query(tm + 1, r, tm + 1, tr, 2 * node + 2));
        }
    }

    void _update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
        i64 tm = tl + (tr - tl) / 2;
        if (tl == p && p == tr){
            seg[node] = x;
        } else {
            if (p <= tm){
                _update(p, x, tl, tm, 2 * node + 1);
            } else {
                _update(p, x, tm + 1, tr, 2 * node + 2);
            }
            seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }
};

// range: -1, i
i64 bsearch_l(i64 i, const i64 pref[], const i64 l){
    // pl = last index such that a[pl] + ... + a[i] >= l
    if (pref[i + 1] < l) {
        return -1;
    }
    i64 lo = 0, hi = i, pl = 0;
    while (lo <= hi){
        i64 m = lo + (hi - lo) / 2;
        // test pl as m
        i64 s = pref[i + 1] - pref[m];  // a[m] + ... + a[i]
        if (s >= l){
            pl = m;
            lo = m + 1;
        } else {
            hi = m - 1;
        }
    }
    return pl;
}

// range: 0, i + 1
i64 bsearch_r(i64 i, const i64 pref[], const i64 r){
    // bsearch for pr
    // pr = first index such that a[pr] + ... + a[i] <= r
    i64 pr = i + 1;
    i64 lo = 0, hi = i + 1;
    while (lo <= hi){
        i64 m = lo + (hi - lo) / 2;
        i64 s = pref[i + 1] - pref[m];  // a[m] + ... + a[i]
        if (s <= r){
            pr = m;
            hi = m - 1;
        } else {
            lo = m + 1;
        }
    }
    return pr;
}

void solve(){
    i64 n;
    i64 l, r;

    cin >> n;
    cin >> l >> r;
    i64 a[n], pref[n + 1], dp[n + 1];
    dp[0] = 0;
    pref[0] = 0;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }

    MaxSeg seg(n + 1);
    for (i64 i = 0; i < n; i++){
        i64 pl = bsearch_l(i, pref, l);
        i64 pr = bsearch_r(i, pref, r);
        i64 new_value = seg.query(pr, pl);
        seg.update(i + 1, max(dp[i], new_value + 1));
        dp[i + 1] = max(dp[i], new_value + 1);
    }
    cout << dp[n] << endl;
}
 
signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
	int t;
#ifdef TESTCASES
	cin >> t;
#else
	t = 1;
#endif
	while (t--){
		solve();
	}
}
