// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)


struct Node {
    i64 l, r, pref, suf, q, lazy;
    // pref: largest alternating subarray at start
    // suf: largest alternating subarray at end

    Node(i64 l) : l(l), r(l), pref(1), suf(1), q(1), lazy(0) {}
    Node() : l(-1), r(-1), pref(0), suf(0), q(0), lazy(0) {}
};

struct SubarraySeg {
    vector<Node> seg;
    const i64 n;

    SubarraySeg(const vector<i64>& a) : n(a.size()) {
        seg.resize(4 * n);

        build(a, 0, n - 1, 0);
    }

    void compose(i64 l, i64 m, i64 r, i64 node){
        prop(2 * node + 1);
        prop(2 * node + 2);
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

        seg[node].q = (seg[2 * node + 1].q + seg[2 * node + 2].q);
        if (seg[2 * node + 1].r != seg[2 * node + 2].l){
            seg[node].q += (
                seg[2 * node + 1].suf * seg[2 * node + 2].pref
            );
        }
    }

    void prop(i64 node){
        // apply lazy
        seg[node].l ^= seg[node].lazy;
        seg[node].r ^= seg[node].lazy;
        // non-unitary
        if (2 * node + 2 < 4 * n){
            seg[2 * node + 1].lazy ^= seg[node].lazy;
            seg[2 * node + 2].lazy ^= seg[node].lazy;
        }
        seg[node].lazy = 0;
    }

    void build(const vector<i64>& a, i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = Node(a[l]);
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
            return seg[node].q;
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm){
                return _query(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                return _query(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                i64 x1 = _query(l, tm, tl, tm, 2 * node + 1);
                i64 x2 = _query(tm + 1, r, tm + 1, tr, 2 * node + 2);
                i64 ans = x1 + x2;
                if (seg[2 * node + 1].r != seg[2 * node + 2].l){
                    ans += (
                        min(seg[2 * node + 1].suf, (tm - l + 1))
                        * min(seg[2 * node + 2].pref, (r - tm))
                    );
                }
                return ans;
            }
        }
    }

    i64 _read_node(i64 pos, i64 tl, i64 tr, i64 node, i64 acc_lazy = 0){
        acc_lazy ^= seg[node].lazy;
        if (tl == pos && pos == tr){
            return seg[node].l ^ acc_lazy;
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (pos <= tm){
                return _read_node(pos, tl, tm, 2 * node + 1, acc_lazy);
            } else {
                return _read_node(pos, tm + 1, tr, 2 * node + 2, acc_lazy);
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
            compose(tl, tm, tr, node);
        }
    }

    i64 query(i64 l, i64 r){
        return _query(l, r, 0, n - 1, 0);
    }

    void update(i64 l, i64 r){
        _update(l, r, 0, n - 1, 0);
    }
};

string str(SubarraySeg& seg){
    string s = "";
    for (i64 i = 0; i < seg.n; i++){
        s += to_string(seg._read_node(i, 0, seg.n - 1, 0)) + " ";
    }
    return s;
}


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