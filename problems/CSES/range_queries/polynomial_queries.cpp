// #define TESTCASES
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

template<typename T, typename U>
void operator+=(pair<T, U>& p, const pair<T, U> q){
    p.first += q.first;
    p.second += q.second;
}
template<typename T, typename U>
void operator-=(pair<T, U>& p, const pair<T, U> q){
    p.first -= q.first;
    p.second -= q.second;
}

struct LazyPolySeg {
    // lz[node] = {a,b} means we should add a * i + b to each position i on the CHILDREN of node
    // (so it was propagated to node, but not to the children)
    vector<pair<i64, i64>> lz;
    vector<i64> seg;
    const i64 n;

    LazyPolySeg(const vector<i64>& a) : n(a.size()) {
        seg.assign(4 * n, 0);
        lz.assign(4 * n, {0, 0});
        build(0, n - 1, 0, a);
    }

    i64 query(const i64 l, const i64 r){
        return _query(l, r, 0, n - 1, 0);
    }

    // add i+1 to i-th element of [l,...,r] (i=0...r-l)
    // which is equivalent of adding p+1-l to element at position p of range
    void update(const i64 l, const i64 r){
        _range_update(1, 1 - l, l, r, 0, n - 1, 0);
    }
private:
    // arithmethic progression sum
    i64 sumAP(i64 a, i64 b){
        return ((b * (b + 1)) / 2) - (((a - 1) * a) / 2);
    }

    void build(const i64 l, const i64 r, const i64 node, const vector<i64>& a){
        if (l == r){
            seg[node] = a[l];
        } else {
            const i64 m = l + (r - l) / 2;
            build(l, m, 2 * node + 1, a);
            build(m + 1, r, 2 * node + 2, a);
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }

    // propagate down the lazy on the children
    void prop(const i64 l, const i64 r, const i64 node){
        auto[a, b] = lz[node];
        lz[node] = {0, 0};
        if (l < r){
            const i64 m = l + (r - l) / 2;
            // apply lazy down
            seg[2 * node + 1] += a * sumAP(l, m) + b * (m - l + 1);
            seg[2 * node + 2] += a * sumAP(m + 1, r) + b * (r - m);
            lz[2 * node + 1] += {a, b};
            lz[2 * node + 2] += {a, b};
        }
    }

    // adds ax + b to each position x in [l,r]
    void _range_update(const i64 a, const i64 b, const i64 l, const i64 r, const i64 tl, const i64 tr, const i64 node){
        const i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr){
            seg[node] += a * sumAP(l, r) + b * (r - l + 1);
            lz[node] += {a, b};
        } else {
            // propagate before entering children to update them
            prop(tl, tr, node);
            // update sum on current node [tl, tr] (which definitely contains [l, r])
            if (r <= tm){
                _range_update(a, b, l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                _range_update(a, b, l, r, tm + 1, tr, 2 * node + 2);
            } else {
                _range_update(a, b, l, tm, tl, tm, 2 * node + 1);
                _range_update(a, b, tm + 1, r, tm + 1, tr, 2 * node + 2);
            }
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }

    i64 _query(const i64 l, const i64 r, const i64 tl, const i64 tr, const i64 node){
        const i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr){
            return seg[node];
        } else {
            // propagate before entering children to update them
            prop(tl, tr, node);
            if (r <= tm){
                return _query(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                return _query(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                return _query(l, tm, tl, tm, 2 * node + 1) + _query(tm + 1, r, tm + 1, tr, 2 * node + 2);
            }
        }
    }
};


void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    LazyPolySeg seg(a);
    for (i64 i = 0; i < q; i++){
        i64 mode, l, r;
        cin >> mode >> l >> r;
        --l; --r;  // to 0-INDEX
        if (mode == 1){
            // update
            seg.update(l, r);
        } else {
            // query
            cout << seg.query(l, r) << endl;
        }
    }
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
