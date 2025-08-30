// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

struct SumSeg {
    i64 n;
    vector<i64> seg;

    SumSeg(i64 sz) : n(sz) {
        seg.assign(4 * n, 0);
    }

    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr) return seg[node];
        else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm){
                return _query(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                return _query(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                return _query(l, tm, tl, tm, 2 * node + 1)
                    + _query(tm + 1, r, tm + 1, tr, 2 * node + 2);
            }
        }
    }
    i64 query(i64 l, i64 r) {
        return _query(l, r, 0, n - 1, 0);
    }

    void _update(i64 p, i64 delta, i64 tl, i64 tr, i64 node){
        const i64 tm = tl + (tr - tl) / 2;
        if (tl == p && p == tr){
            seg[node] += delta;
        } else {
            if (p <= tm) _update(p, delta, tl, tm, 2 * node + 1);
            else _update(p, delta, tm + 1, tr, 2 * node + 2);
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }

    void update(i64 p, i64 delta) {
        _update(p, delta, 0, n - 1, 0);
    }
};

void solve(){
    i64 n;
    cin >> n;
    vector<pair<i64,i64>> ad(n);
    for (i64 i = 0; i < n; i++){
        cin >> ad[i].first >> ad[i].second;
    }
    i64 a1, a2, d1, d2;
    cin >> a1 >> d1 >> a2 >> d2;

    vector<pair<i64, i64>> halfs[2];
    set<i64> ys;
    i64 n1 = n / 2, n2 = n - n1;
    for (i64 msk = 0; msk < (1ll << n1); msk++){
        i64 x = 0, y = 0;
        for (i64 i = 0; i < n1; i++){
            if (msk & (1ll << i)){
                x += ad[i].first;
                y += ad[i].second;
            }
        }
        ys.insert(y);
        halfs[0].emplace_back(x, y);
    }
    for (i64 msk = 0; msk < (1ll << n2); msk++){
        i64 x = 0, y = 0;
        for (i64 i = 0; i < n2; i++){
            if (msk & (1ll << i)){
                x += ad[i + n1].first;
                y += ad[i + n1].second;
            }
        }
        ys.insert(y);
        halfs[1].emplace_back(x, y);
    }

    // compress coordinates
    vector<i64> _ys(ys.size());
    copy(all(ys), _ys.begin());
    auto compressY = [&_ys](i64 y){
        return lower_bound(all(_ys), y) - _ys.begin();
    };

    // will build sliding window of x values
    // must be in decreasing order of x1, increasing in x2
    sort(all(halfs[0]));
    reverse(all(halfs[0]));
    sort(all(halfs[1]));

    i64 l = 0, r = -1;
    const i64 unique_k = ys.size(), k = halfs[1].size();
    SumSeg seg(unique_k);
    i64 ans = 0;
    for (auto[x, y]: halfs[0]){
        while (r + 1 < k && x + halfs[1][r + 1].first <= a2){
            seg.update(compressY(halfs[1][r + 1].second), +1);
            ++r;
        }
        while (l <= r && x + halfs[1][l].first < a1){
            // exclude l-th element (move sliding window)
            // can only delete was is already there (so <= r)
            seg.update(compressY(halfs[1][l].second), -1);
            ++l;
        }
        // y' must satisfy
        // d1 <= y + y' <= d2
        // y' >= d1 - y AND !(y' >= d2 - y + 1)
        i64 ly = compressY(d1 - y), ry = compressY(d2 - y + 1) - 1;
        if (ly <= ry){
            ans += seg.query(ly, ry);
        }
    }
    cout << ans << endl;
}
 
signed main(){
	fastio;
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
