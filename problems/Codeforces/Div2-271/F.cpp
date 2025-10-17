// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
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

struct GCDCountSeg {
    i64 n;
    vector<i64> range_gcd, count_gcd;

    GCDCountSeg(i64 n) : n(n), range_gcd(4 * n), count_gcd(4 * n) {}
    GCDCountSeg(const vector<i64>& a) : n(a.size()), range_gcd(4 * a.size()), count_gcd(4 * a.size()) {
        for (i64 i = 0; i < n; i++) update(i, a[i]);
    }

    inline pair<i64, i64> merge(pair<i64, i64> p1, pair<i64, i64> p2){
        auto[g1, c1] = p1;
        auto[g2, c2] = p2;
        i64 g = gcd(g1, g2);
        return {g, c1 * (g == g1) + c2 * (g == g2)};
    }

    void _update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
        const i64 tm = tl + (tr - tl) / 2;
        if (tl == p && p == tr){
            range_gcd[node] = x;
            count_gcd[node] = 1;
        } else {
            if (p <= tm) _update(p, x, tl, tm, 2 * node + 1);
            else _update(p, x, tm + 1, tr, 2 * node + 2);
            tie(range_gcd[node], count_gcd[node]) = merge(
                make_pair(range_gcd[2 * node + 1], count_gcd[2 * node + 1]),
                make_pair(range_gcd[2 * node + 2], count_gcd[2 * node + 2])
            );
        }
    }

    void update(i64 p, i64 x) { _update(p, x, 0, n - 1, 0); }

    pair<i64, i64> _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr){
            return make_pair(range_gcd[node], count_gcd[node]);
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm) return _query(l, r, tl, tm, 2 * node + 1);
            else if (l > tm) return _query(l, r, tm + 1, tr, 2 * node + 2);
            else return merge(
                _query(l, tm, tl, tm, 2 * node + 1),
                _query(tm + 1, r, tm + 1, tr, 2 * node + 2)
            );
        }
    }

    pair<i64, i64> query(i64 l, i64 r) { return _query(l, r, 0, n - 1, 0); }
};

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];
    GCDCountSeg seg(a);
    i64 q;
    cin >> q;
    for (i64 i = 0; i < q; i++){
        i64 l, r;
        cin >> l >> r;
        --l; --r;
        i64 total = r - l + 1;
        auto[_, freed] = seg.query(l, r);
        cout << total - freed << endl;
    }
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
