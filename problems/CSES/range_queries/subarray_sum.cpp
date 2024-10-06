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

const i64 SUM = 1;
const i64 PREFIX = 2;
const i64 SUFFIX = 3;
const i64 SUBARRAY = 4;
 
template<typename T>
struct SubarraySumTree {
    vector<T> seg;
    vector<T> prefix_seg, suffix_seg, subarray_seg;
 
    // constructor
    SubarraySumTree(const vector<T> a){
        const i64 n = a.size();
        vector<T> b = a;
        seg.resize(4 * n);
        prefix_seg.resize(4 * n);
        suffix_seg.resize(4 * n);
        subarray_seg.resize(4 * n);
        build(b, 0, n - 1, 0, SUM);
        build(b, 0, n - 1, 0, PREFIX);
        build(b, 0, n - 1, 0, SUFFIX);
        build(b, 0, n - 1, 0, SUBARRAY);
    }
 
    i64 build(vector<T>& a, i64 l, i64 r, i64 node, i64 MODE){
        if (l == r){
            if (MODE == SUM){
                seg[node] = a[l];
                return seg[node];
            } else if (MODE == PREFIX){
                prefix_seg[node] = a[l];
                return prefix_seg[node];
            } else if (MODE == SUFFIX){
                suffix_seg[node] = a[l];
                return suffix_seg[node];
            } else {
                subarray_seg[node] = a[l];
                return subarray_seg[node];
            }
        } else {
            i64 m = l + (r - l) / 2;
            i64 lvalue = build(a, l, m, 2 * node + 1, MODE);
            i64 rvalue = build(a, m + 1, r, 2 * node + 2, MODE);
            if (MODE == SUM){
                seg[node] = lvalue + rvalue;
                return seg[node];
            } else if (MODE == PREFIX){
                prefix_seg[node] = max(prefix_seg[2 * node + 1], seg[2 * node + 1] + prefix_seg[2 * node + 2]);
                return prefix_seg[node];
            } else if (MODE == SUFFIX){
                suffix_seg[node] = max(suffix_seg[2 * node + 1] + seg[2 * node + 2], suffix_seg[2 * node + 2]);
                return suffix_seg[node];
            } else {
                subarray_seg[node] = max(subarray_seg[2 * node + 1],
                    max(subarray_seg[2 * node + 2], suffix_seg[2 * node + 1] + prefix_seg[2 * node + 2])
                );
                return subarray_seg[node];
            }
        }
    }
 
    T query(i64 l, i64 r, i64 tree_l, i64 tree_r, i64 node, i64 MODE){
        i64 mid = tree_l + (tree_r - tree_l) / 2;
        if (tree_l == l && tree_r == r){
            if (MODE == SUM){
                return seg[node];
            } else if (MODE == PREFIX){
                return prefix_seg[node];
            } else if (MODE == SUFFIX){
                return suffix_seg[node];
            } else {
                return subarray_seg[node];
            }
        } else if (r <= mid){
            return query(l, r, tree_l, mid, 2 * node + 1, MODE);
        } else if (l > mid){
            return query(l, r, mid + 1, tree_r, 2 * node + 2, MODE);
        } else {
            i64 lvalue = query(l, mid, tree_l, mid, 2 * node + 1, MODE);
            i64 rvalue = query(mid + 1, r, mid + 1, tree_r, 2 * node + 2, MODE);
            if (MODE == SUM){
                return lvalue + rvalue;
            } else if (MODE == PREFIX){
                i64 total = query(l, mid, tree_l, mid, 2 * node + 1, SUM);
                return max(lvalue, total + rvalue);
            } else if (MODE == SUFFIX){
                i64 total = query(mid + 1, r, mid + 1, tree_r, 2 * node + 1, SUM);
                return max(lvalue + total, rvalue);
            } else {
                i64 suf = query(l, mid, tree_l, mid, 2 * node + 1, SUFFIX);
                i64 pref = query(mid + 1, r, mid + 1, tree_r, 2 * node + 2, PREFIX);
                return max(lvalue, max(rvalue, suf + pref));
            }
        }
    }
 
    void update(i64 p, T x, i64 l, i64 r, i64 node){
        if (l == p && p == r){
            seg[node] = x;
            prefix_seg[node] = x;
            suffix_seg[node] = x;
            subarray_seg[node] = x;
        } else {
            i64 m = l + (r - l) / 2;
            if (p <= m){
                update(p, x, l, m, 2 * node + 1);
            } else {
                update(p, x, m + 1, r, 2 * node + 2);
            }
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
            prefix_seg[node] = max(prefix_seg[2 * node + 1], seg[2 * node + 1] + prefix_seg[2 * node + 2]);
            suffix_seg[node] = max(suffix_seg[2 * node + 1] + seg[2 * node + 2], suffix_seg[2 * node + 2]);
            subarray_seg[node] = max(subarray_seg[2 * node + 1],
                max(subarray_seg[2 * node + 2], suffix_seg[2 * node + 1] + prefix_seg[2 * node + 2])
            );
        }
    }
};
 
vector<i64> arr;
 
void solve(){
    i64 n, q;
    i64 k, x;
    cin >> n >> q;

    arr.resize(n);
    for (i64 i = 0; i < n; i++){
        cin >> arr[i];
    }

    SubarraySumTree<i64> seg(arr);
    for (i64 i = 0; i < q; i++){
        cin >> k >> x;
        --k;  // 0-index
        seg.update(k, x, 0, n - 1, 0);
        cout << max(seg.query(0, n - 1, 0, n - 1, 0, SUBARRAY), (i64)0) << endl;
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
