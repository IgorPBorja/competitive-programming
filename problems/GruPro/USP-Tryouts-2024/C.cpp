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

// cyclic sum seg
// seg for node [l,r]
// is min_{l <= k <= r}(sum_{j=l..k}(b[j]-c[j]))
struct CyclicSeg {
    i64 n;
    vector<i64> sumseg;
    vector<i64> minseg;
    vector<i64> b, c;

    CyclicSeg(vector<i64> _b, vector<i64> _c) : n(2 * _b.size()) {
        sumseg.resize(4 * n);
        minseg.resize(4 * n);
        b.resize(n);
        c.resize(n);
        for (i64 i = 0; i < n; i++){
            _update(i, _b[i % _b.size()], _c[i % _c.size()], 0, n - 1, 0);
        }
    }

    pair<i64, i64> _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr) return {minseg[node], sumseg[node]};
        const i64 tm = tl + (tr - tl) / 2;
        if (r <= tm) return _query(l, r, tl, tm, 2 * node + 1);
        else if (l > tm) return _query(l, r, tm + 1, tr, 2 * node + 2);
        else {
            auto[m1, s1] = _query(l, tm, tl, tm, 2 * node + 1);
            auto[m2, s2] = _query(tm + 1, r, tm + 1, tr, 2 * node + 2);
            return {min(m1, s1 + m2), s1 + s2};
        }
    }

    i64 query(i64 l, i64 r){
        return _query(l, r, 0, n - 1, 0).first;
    }

    i64 lb(i64 i){
        assert(i < n / 2);
        i64 l = i, r = i + n / 2 - 1;  // last pos before
        i64 ans = l - 1;
        while (l <= r){
            const i64 m = l + (r - l) / 2;
            i64 s = query(i, m);
            if (s >= 0){
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (ans == i + n / 2 - 1) { // full cycle
            return -1;
        } else return (ans + 1) % (n/2);  // can take ans->ans+1 edge as final edge
        // however this might cross n->n+1 so we need to take mod
    }

    void _update(i64 p, i64 delta_b, i64 delta_c, i64 tl, i64 tr, i64 node){
        if (tl == p && p == tr){
            sumseg[node] = minseg[node] = (b[p] + delta_b) - (c[p] + delta_c);
            b[p] += delta_b;
            c[p] += delta_c;
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (p <= tm) _update(p, delta_b, delta_c, tl, tm, 2 * node + 1);
            else _update(p, delta_b, delta_c, tm + 1, tr, 2 * node + 2);
            sumseg[node] = sumseg[2 * node + 1] + sumseg[2 * node + 2];
            minseg[node] = min(minseg[2 * node + 1], sumseg[2 * node + 1] + minseg[2 * node + 2]);
        }
    }

    void update_b(i64 p, i64 new_b){
        assert(p < n / 2);
        _update(p, new_b - b[p], 0, 0, n - 1, 0);
        _update(p + n / 2, new_b - b[p + n / 2], 0, 0, n - 1, 0);
    }

    void update_c(i64 p, i64 new_c){
        assert(p < n / 2);
        _update(p, 0, new_c - c[p], 0, n - 1, 0);
        _update(p + n / 2, 0, new_c - c[p + n / 2], 0, n - 1, 0);
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;

    vector<i64> b(n), c(n);
    for (i64 i = 0; i < n; i++){
        cin >> b[i];
    }
    for (i64 i = 0; i < n; i++){
        cin >> c[i];
    }
    CyclicSeg seg(b, c);
    // printmsg("seg=", seg.seg.begin(), seg.seg.end());
    // printmsg("cyc b=", seg.b.begin(), seg.b.end());
    // printmsg("cyc c=", seg.c.begin(), seg.c.end());

    for (i64 _ = 0; _ < q; _++){
        i64 mode, i, x;
        cin >> mode;
        cin >> i;
        --i;
        if (mode == 1){
            i64 last_pos = seg.lb(i);
            cout << (last_pos == -1 ? -1 : last_pos + 1) << endl;
        } else if (mode == 2){
            cin >> x;
            seg.update_b(i, x);
        } else {
            cin >> x;
            seg.update_c(i, x);
        }
        // printmsg("seg=", seg.seg.begin(), seg.seg.end());
        // printmsg("cyc b=", seg.b.begin(), seg.b.end());
        // printmsg("cyc c=", seg.c.begin(), seg.c.end());
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
