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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

struct Node {
    i64 pref, suf, subarr, total;

    Node() {}
    Node(i64 x) {
        i64 best = max(x, (i64)0);
        pref = best;
        suf = best;
        subarr = best;
        total = x;
    }
    Node(i64 pref, i64 suf, i64 subarr, i64 total) : pref(pref), suf(suf),
        subarr(subarr), total(total) {}
};
 
struct SubarraySumTree {
    vector<Node> seg;
    i64 n;
 
    // constructor
    SubarraySumTree(const vector<i64> a) : n(a.size()) {
        seg.resize(4 * n);
        build(a, 0, n - 1, 0);
    }

    Node merge(const Node n1, const Node n2){
        Node merged;
        merged.pref = max(n1.pref, n1.total + n2.pref);
        merged.suf = max(n2.suf, n1.suf + n2.total);
        merged.subarr = max(max(n1.subarr, n2.subarr), n1.suf + n2.pref);
        merged.total = n1.total + n2.total;
        return merged;
    }
 
    void build(const vector<i64>& a, i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = Node(a[l]);
        } else {
            i64 m = l + (r - l) / 2;
            build(a, l, m, 2 * node + 1);
            build(a, m + 1, r, 2 * node + 2);
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }
 
    Node _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        i64 tm = tl + (tr - tl) / 2;
        if (tl == l && tr == r){
            return seg[node];
        } else if (r <= tm){
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

    i64 query(i64 l, i64 r) { return _query(l, r, 0, n - 1, 0).subarr; }
 
    void update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
        if (tl == p && p == tr){
            seg[node] = Node(x);
        } else {
            i64 tm = tl + (tr - tl) / 2;
            if (p <= tm){
                update(p, x, tl, tm, 2 * node + 1);
            } else {
                update(p, x, tm + 1, tr, 2 * node + 2);
            }
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }
};
 
void solve(){
    i64 n, q;
    i64 l, r;
    cin >> n >> q;

    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    SubarraySumTree seg(a);
    for (i64 i = 0; i < q; i++){
        cin >> l >> r;
        --l; --r;  // 0-index
        cout << seg.query(l, r) << endl;
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
