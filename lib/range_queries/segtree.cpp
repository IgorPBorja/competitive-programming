#include <bits/stdc++.h>
using namespace std;

const int INF = (int)2e9;
 
// default seg tree (in this example, a Max Seg)
struct MaxSegTree {
    vector<int> seg;
    vector<int> a;
    int n;

    MaxSegTree(int n, int val = -INF) : n(n) {
        seg.assign(4 * n, val);
        a.assign(n, val);
    }

    int query(int l, int r){
        return _query(l, r, 0, n - 1, 0);
    }

    void update(int p, int x){
        _update(p, x, 0, n - 1, 0);
    }

private:
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
                return max(
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
            seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }
};