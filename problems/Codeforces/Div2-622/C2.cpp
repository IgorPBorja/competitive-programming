// #define testcases
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define int long long
#define i64 int64_t
#define printmsg(msg, first, last) cout << msg; for (auto it = first; it != last; it++) cout << *it << " "; cout << endl


template <typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> p){
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

const i64 INF = (i64)2e18;

struct ArgminSeg {
    vector<i64> argmin, a;
    i64 n;
    ArgminSeg(const vector<i64>& a) : a(a), n(a.size()) {
        argmin.resize(4 * n);
        build(0, n - 1, 0);
    }
    
    void build(i64 l, i64 r, i64 node) {
        if (l == r){
            argmin[node] = l;
        } else {
            const i64 m = l + (r - l) / 2;
            build(l, m, 2 * node + 1);
            build(m + 1, r, 2 * node + 2);
            if (a[argmin[2 * node + 2]] < a[argmin[2 * node + 1]]){
                argmin[node] = argmin[2 * node + 2];
            } else {
                argmin[node] = argmin[2 * node + 1];
            }
        }
    }
    
    i64 range_argmin(i64 l, i64 r) const {
        return _range_argmin(l, r, 0, n - 1, 0);
    }
    
    i64 _range_argmin(i64 l, i64 r, i64 tl, i64 tr, i64 node) const {
        if (l == tl && r == tr){
            return argmin[node];
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm){
                return _range_argmin(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm) {
                return _range_argmin(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                i64 idx1 = _range_argmin(l, tm, tl, tm, 2 * node + 1);
                i64 idx2 = _range_argmin(tm + 1, r, tm + 1, tr, 2 * node + 2);
                if (a[idx2] < a[idx1]){
                    return idx2;
                } else {
                    return idx1;
                }
            }
        }
    }
};

struct Node {
    i64 val;
    i64 center, l, r;
    Node *argmin_left, *argmin_right;
    i64 dir;  // 0 is left, 1 is right, -1 is leat
  
    Node(i64 l, i64 r, const ArgminSeg& seg)
    : l(l), r(r), argmin_left(nullptr), argmin_right(nullptr) {
        center = seg.range_argmin(l, r);
        i64 min_v = seg.a[center];
        if (center > l){
            argmin_left = new Node(l, center - 1, seg);
        }
        if (center < r){
            argmin_right = new Node(center + 1, r, seg);
        }

        i64 left_v = (center > l ? argmin_left->val : 0) + (r - center + 1) * min_v;
        i64 right_v = (center < r ? argmin_right->val : 0) + (center - l + 1) * min_v;
        val = max(left_v, right_v);
        // TODO check if the children exist
        if (l == r){
            dir = -1;
        } else if (left_v >= right_v && (argmin_left != nullptr)) {  // might be the case they are all the same, and center is l
            dir = 0;
        } else {
            dir = 1;
        }
    }
};

void fill_array(Node* node, vector<i64>& a, vector<i64>& b){
    i64 min_v = a[node->center];
    if (node->dir == 0){
        // fill right
        for (i64 i = node->center; i <= node->r; i++){
            b[i] = min_v;
        }
        fill_array(node->argmin_left, a, b);
    } else if (node->dir == 1){
        for (i64 i = node->l; i <= node->center; i++){
            b[i] = min_v;
        }
        fill_array(node->argmin_right, a, b);
    } else {
        b[node->center] = min_v;
    }
}

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];
    
    ArgminSeg seg(a);
    Node root(0, n - 1, seg);
    vector<i64> b(n);
    fill_array(&root, a, b);
    for (i64 i = 0; i < n; i++) cout << b[i] << " ";
    cout << endl;
}

signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}
