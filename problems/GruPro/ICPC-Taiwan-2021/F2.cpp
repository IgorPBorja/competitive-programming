// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

struct Node {
    i64 l, r, pref, suf, val, lazy;

    Node(i64 l, i64 r, i64 pref, i64 suf, i64 val) : l(l), r(r), pref(pref), suf(suf), val(val), lazy(0) {}
    Node() : l(-1), r(-1), pref(0), suf(0), val(0), lazy(0) {}
};

struct SubarraySeg {
    vector<Node> seg;
    const i64 n;

    SubarraySeg(const vector<i64>& a) : n(a.size()) {
        seg.resize(4 * n);

        build(a, 0, n - 1, 0);
    }

    void compose(i64 l, i64 m, i64 r, i64 node){
        seg[node].l = seg[2 * node + 1].l;
        seg[node].r = seg[2 * node + 2].r;
        if (
            seg[2 * node + 1].pref == m - l + 1
            && (seg[2 * node + 1].r != seg[2 * node + 2].l)
        ){
            seg[node].pref = m - l + 1 + seg[2 * node + 2].pref;
        } else {
            seg[node].pref = seg[2 * node + 1].pref;
        }
        if (
            seg[2 * node + 2].suf == r - m
            && (seg[2 * node + 1].r != seg[2 * node + 2].l)
        ){
            seg[node].suf = r - m + seg[2 * node + 1].suf;
        } else {
            seg[node].suf = seg[2 * node + 2].suf;
        }
        seg[node].val = max(
            seg[node].pref, seg[node].suf
        );
        if (seg[2 * node + 1].r != seg[2 * node + 2].l){
            seg[node].val = max(seg[node].val, seg[2 * node + 1].suf + seg[2 * node + 2].pref);
        }
    }

    void prop(i64 node){
        seg[node].l ^= seg[node].lazy;
        seg[node].r ^= seg[node].lazy;
        seg[2 * node + 1].lazy ^= seg[node].lazy;
        seg[2 * node + 2].lazy ^= seg[node].lazy;
        seg[node].lazy = 0;
    }

    void build(const vector<i64>& a, i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = Node(a[l], a[r], 1, 1, 1);
        } else {
            const i64 m = l + (r - l) / 2;
            build(a, l, m, 2 * node + 1);
            build(a, m + 1, r, 2 * node + 2);
            compose(l, m, r, node);
        }
    }

    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        prop(node);
        if (l == tl && r == tr){
            return seg[node].val;
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm){
                return _query(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                return _query(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                // just for updating lazy
                _query(l, tm, tl, tm, 2 * node + 1);
                _query(tm + 1, r, tm + 1, tr, 2 * node + 2);
                i64 ans = max(seg[2 * node + 1].val, seg[2 * node + 2].val);
                if (seg[2 * node + 1].r == seg[2 * node + 2].l){
                    ans = max(ans, seg[2 * node + 1].suf + seg[2 * node + 2].pref);
                }
                return ans;
            }
        }
    }

    void _update(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        prop(node);
        if (l == tl && r == tr){
            seg[node].lazy = 1;
            prop(node);
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm){
                _update(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                _update(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                _update(l, tm, tl, tm, 2 * node + 1);
                _update(tm + 1, r, tm + 1, tr, 2 * node + 2);
            }
            compose(node, tl, tm, tr);
        }
    }

    i64 query(i64 l, i64 r){
        return _query(l, r, 0, n - 1, 0);
    }

    void update(i64 l, i64 r){
        _update(l, r, 0, n - 1, 0);
    }
};


void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    SubarraySeg seg(a);
    for (i64 i = 0; i < q; i++){
        i64 mode, l, r;
        cin >> mode >> l >> r;
        --l; --r;
        if (mode == 1){
            seg.update(l, r);
        } else {
            cout << seg.query(l, r) << endl;
        }
    }
}

signed main(){
    i64 t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--){
        solve();
    }
}