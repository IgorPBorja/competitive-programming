#include <bits/stdc++.h>
using namespace std;

// default seg tree (in this example, a Max Seg)
struct SegTree {
    vector<int> seg;
    vector<int> a;
    int n;

    SegTree(const vector<int>& a) : a(a), n(a.size()) {
        seg.resize(4 * n);
        build(0, n - 1, 0);
    }

    inline int merge(int a, int b){
        return max(a, b);  // <--- CHANGE HERE
    }

    void build(int l, int r, int node){
        if (l == r) seg[node] = a[l];
        else {
            const int m = l + (r - l) / 2;
            build(l, m, 2 * node + 1);
            build(m + 1, r, 2 * node + 2);
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    int query(int l, int r){
        return _query(l, r, 0, n - 1, 0);
    }

    void update(int p, int x){
        _update(p, x, 0, n - 1, 0);
    }

    int _query(int l, int r, int tl, int tr, int node){
        if (l == tl && r == tr){
            return seg[node];
        } else {
            int tm = tl + (tr - tl) / 2;
            if (r <= tm){
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

    void _update(int p, int x, int tl, int tr, int node){
        if (tl == p && tr == p){
            seg[node] = x;
            a[p] = x;
        } else {
            int tm = tl + (tr - tl) / 2;
            if (p <= tm){
                _update(p, x, tl, tm, 2 * node + 1);
            } else {
                _update(p, x, tm + 1, tr, 2 * node + 2);
            }
            seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }
};