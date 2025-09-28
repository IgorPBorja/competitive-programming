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
#define print(msg, v) debug << msg; for(auto it = v.begin(); it != v.end(); it++){debug << *it << " ";} debug << endl;
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

/*
process offline: queries "count x >= c on range [a,b]"
for c in decreasing order

Becomes sum query on sum seg over 0-1 array
*/

struct SumSeg {
    i64 n;
    vector<i64> seg;

    SumSeg(i64 _n) : n(_n) {
        seg.assign(4 * n, (i64)0);
    }

    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        const i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr) return seg[node];
        else if (r <= tm) return _query(l, r, tl, tm, 2 * node + 1);
        else if (l > tm) return _query(l, r, tm + 1, tr, 2 * node + 2);
        else return _query(l, tm, tl, tm, 2 * node + 1) + _query(tm + 1, r, tm + 1, tr, 2 * node + 2);
    }
    i64 query(i64 l, i64 r) { return _query(l, r, 0, n - 1, 0); }

    void _inc(i64 p, i64 tl, i64 tr, i64 node){
        if (tl == p && p == tr) ++seg[node];
        else {
            const i64 tm = tl + (tr - tl) / 2;
            if (p <= tm) _inc(p, tl, tm, 2 * node + 1);
            else _inc(p, tm + 1, tr, 2 * node + 2);
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }
    void inc(i64 p) { _inc(p, 0, n - 1, 0); }
};

void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> x(n);
    vector<pair<i64, i64>> updates(n);
    for (i64 i = 0; i < n; i++){
        cin >> x[i];
        updates[i] = make_pair(x[i], i);
    }
    sort(all(updates));
    reverse(all(updates));

    vector<tuple<i64, i64, i64, i64>> queries(q);
    vector<tuple<i64, i64, i64, i64>> query_splits(2 * q);
    vector<i64> answer_splits(2 * q);
    for (i64 i = 0; i < q; i++){
        i64 a, b, c, d;
        cin >> a >> b >> c >> d;
        --a; --b;
        queries[i] = make_tuple(a, b, c, d);
        // split query "#(x_i: a <= i <= b, c <= x_i <= d)"
        // in "#(x_i: a <= i <= b, c <= x_i)" - "#(x_i: a <= i <= b, d + 1 <= x_i)"
        query_splits[2 * i] = make_tuple(c, a, b, 2 * i);
        query_splits[2 * i + 1] = make_tuple(d + 1, a, b, 2 * i + 1);
    }
    sort(all(query_splits));
    reverse(all(query_splits));

    i64 l = 0;
    SumSeg seg(n);
    for (i64 i = 0; i < 2 * q; i++){
        auto[c, a, b, j] = query_splits[i];
        // cout << "PROCESSING c=" << c << endl;
        // add new
        while (l < n && updates[l].first >= c) {
            auto[_, p] = updates[l];
            seg.inc(p);
            ++l;
            // cout << "increased at p=" << p << endl;
        }
        // cout << "query(" << c << "," << a << "," << b << ")=" << seg.query(a, b) << endl;
        answer_splits[j] = seg.query(a, b);
    }

    for (i64 i = 0; i < q; i++){
        cout << answer_splits[2 * i] - answer_splits[2 * i + 1] << endl;
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
