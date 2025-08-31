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

struct MaxMinSeg {
    i64 n;
    vector<i64> a, maxs, mins;
    
    MaxMinSeg(const vector<i64>& v) : n(v.size()), a(v) {
        maxs.resize(4 * n);
        mins.resize(4 * n);
        build(0, n - 1, 0);
    }

    void build(i64 l, i64 r, i64 node){
        if (l == r){
            maxs[node] = mins[node] = a[l];
        } else {
            const i64 m = l + (r - l) / 2;
            build(l, m, 2 * node + 1);
            build(m + 1, r, 2 * node + 2);
            maxs[node] = max(maxs[2 * node + 1], maxs[2 * node + 2]);
            mins[node] = min(mins[2 * node + 1], mins[2 * node + 2]);
        }
    }

    inline pair<i64, i64> merge(pair<i64, i64> p1, pair<i64, i64> p2){
        return {min(p1.first, p2.first), max(p1.second, p2.second)};
    }

    pair<i64, i64> _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr) return {mins[node], maxs[node]};
        else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm) {
                return _query(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                return _query(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                return merge(
                    _query(l, tm, tl, tm, 2 * node + 1),
                    _query(tm + 1, r, tm + 1, tr, 2 * node + 2)
                );
            }
        }
    }

    // since all values are distinct, is permutation
    // iff minimum on range is 1 and maximum is range size
    bool is_permutation(i64 l, i64 r){
        auto[m, M] = _query(l, r, 0, n - 1, 0);
        return (m == 1) && (M == (r - l + 1));
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    MaxMinSeg seg(a);
    for (i64 i = 0; i < q; i++){
        i64 l, r;
        cin >> l >> r;
        --l; --r;
        cout << (seg.is_permutation(l, r) ? "TAK" : "NIE") << endl;
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
