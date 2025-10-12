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

/*
range for nim winner (XOR)
with point updates
*/

struct XORSeg {
    vector<i64> seg;
    i64 n;

    XORSeg(vector<i64> a) : seg(4 * a.size()), n(a.size()) {
        fill(all(seg), 0);
        for (i64 i = 0; i < n; i++){
            update(i, a[i]);
        }
    }

    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        const i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr){
            return seg[node];
        } else if (r <= tm){
            return _query(l, r, tl, tm, 2 * node + 1);
        } else if (l > tm){
            return _query(l, r, tm + 1, tr, 2 * node + 2);
        } else {
            return _query(l, tm, tl, tm, 2 * node + 1) ^ _query(tm + 1, r, tm + 1, tr, 2 * node + 2);
        }
    }

    // return 0 or 1, index of winner player
    i64 query(i64 l, i64 r){
        i64 range_xor = _query(l, r, 0, n - 1, 0);
        return (range_xor > 0 ? 0 : 1);
    }

    void _update(i64 p, i64 delta, i64 tl, i64 tr, i64 node){
        if (tl == p && p == tr){
            seg[node] += delta;
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (p <= tm){
                _update(p, delta, tl, tm, 2 * node + 1);
            } else {
                _update(p, delta, tm + 1, tr, 2 * node + 2);
            }
            seg[node] = seg[2 * node + 1] ^ seg[2 * node + 2];
        }
    }

    void update(i64 p, i64 delta){
        _update(p, delta, 0, n - 1, 0);
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];

    XORSeg seg(a);
    string players[2] = {"FRANK", "JUAN"};

    for (i64 i = 0; i < q; i++){
        string mode;
        i64 l, r, k, x;
        cin >> mode;
        if (mode == "P"){
            cin >> l >> r;
            --l; --r;
            cout << players[seg.query(l, r)] << endl;
        } else {
            cin >> k >> x;
            --k;
            seg.update(k, x);
        }
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
