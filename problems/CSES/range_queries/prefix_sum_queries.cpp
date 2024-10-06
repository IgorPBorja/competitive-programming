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

template<typename T>
struct SumSegTree {
    vector<T> seg;
    vector<T> prefix_seg;

    // constructor
    SumSegTree(const vector<T> a){
        const i64 n = a.size();
        vector<T> b = a;
        seg.resize(4 * n);
        seg.assign(4 * n, (i64)0);
        build(b, 0, n - 1, 0);
        prefix_seg.resize(4 * n);
        prefix_seg.assign(4 * n, (i64)(-2e18));
        build_prefix(b, 0, n - 1, 0);
    }

    i64 build(vector<T>& a, i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = a[l];
        } else {
            i64 m = l + (r - l) / 2;
            i64 lvalue = build(a, l, m, 2 * node + 1);
            i64 rvalue = build(a, m + 1, r, 2 * node + 2);
            seg[node] = lvalue + rvalue;
        }
        return seg[node];
    }

    i64 build_prefix(vector<T>& a, i64 l, i64 r, i64 node){
        if (l == r){
            prefix_seg[node] = a[l];
        } else {
            i64 m = l + (r - l) / 2;
            i64 lvalue = build_prefix(a, l, m, 2 * node + 1);
            i64 lvalue_total = query_sum(l, m, 0, a.size() - 1, 0);
            i64 rvalue = build_prefix(a, m + 1, r, 2 * node + 2);
            prefix_seg[node] = max(lvalue, lvalue_total + rvalue);
        }
        return prefix_seg[node];
    }

    T query_sum(i64 l, i64 r, i64 tree_l, i64 tree_r, i64 node){
        i64 mid = tree_l + (tree_r - tree_l) / 2;
        if (tree_l == l && tree_r == r){
            return seg[node];
        } else if (r <= mid){
            return query_sum(l, r, tree_l, mid, 2 * node + 1);
        } else if (l > mid){
            return query_sum(l, r, mid + 1, tree_r, 2 * node + 2);
        } else {
            return query_sum(l, mid, tree_l, mid, 2 * node + 1) + query_sum(mid + 1, r, mid + 1, tree_r, 2 * node + 2);
        }
    }

    T query_prefix(i64 l, i64 r, i64 tree_l, i64 tree_r, i64 node){
        i64 mid = tree_l + (tree_r - tree_l) / 2;
        if (l == tree_l && r == tree_r){
            return prefix_seg[node];
        } else if (r <= mid){
            return query_prefix(l, r, tree_l, mid, 2 * node + 1);
        } else if (l > mid){
            return query_prefix(l, r, mid + 1, tree_r, 2 * node + 2);
        } else {
            i64 left_prefix = query_prefix(l, mid, tree_l, mid, 2 * node + 1);
            i64 left_sum = query_sum(l, mid, tree_l, mid, 2 * node + 1);
            i64 right_prefix = query_prefix(mid + 1, r, mid + 1, tree_r, 2 * node + 2);
            return max(left_prefix, left_sum + right_prefix);
        }
    }

    void _update_sum(i64 p, T x, i64 tree_l, i64 tree_r, i64 node){
        i64 mid = tree_l + (tree_r - tree_l) / 2;
        if (tree_l == p && p == tree_r){
            seg[node] = x;
        } else {
            if (p <= mid){
                _update_sum(p, x, tree_l, mid, 2 * node + 1);
            } else {
                _update_sum(p, x, mid + 1, tree_r, 2 * node + 2);
            }
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }

    void _update_prefix(i64 p, T x, i64 tree_l, i64 tree_r, i64 node){
        i64 mid = tree_l + (tree_r - tree_l) / 2;
        if (tree_l == p && p == tree_r){
            prefix_seg[node] = x;
        } else {
            if (p <= mid){
                _update_prefix(p, x, tree_l, mid, 2 * node + 1);
            } else {
                _update_prefix(p, x, mid + 1, tree_r, 2 * node + 2);
            }
            prefix_seg[node] = max(prefix_seg[2 * node + 1], seg[2 * node + 1] + prefix_seg[2 * node + 2]);
        }
    }

    void update(i64 p, T x){
        _update_sum(p, x, 0, seg.size() / 4 - 1, 0);
        _update_prefix(p, x, 0, seg.size() / 4 - 1, 0);
    }
};

vector<i64> arr;

void solve(){
    i64 n, q;
    cin >> n >> q;
    arr.resize(n);
    for (i64 i = 0; i < n; i++){
        cin >> arr[i];
    }
    SumSegTree<i64> seg(arr);

    i64 mode, a, b, k, x;
    for (i64 i = 0; i < q; i++){
        cin >> mode;
        if (mode == 1){
            cin >> k >> x;
            seg.update(--k, x);
        } else {
            cin >> a >> b;
            i64 ans = seg.query_prefix(--a, --b, 0, n - 1, 0);
            cout << max(ans, (i64)0) << endl;
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
