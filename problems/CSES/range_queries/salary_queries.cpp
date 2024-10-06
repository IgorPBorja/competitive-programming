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

    // constructor
    SumSegTree(const vector<T> a, T default_value){
        const i64 n = a.size();
        vector<T> b = a;
        seg.resize(4 * n);
        seg.assign(4 * n, default_value);
        build(b, 0, n - 1, 0);
    }

    void build(vector<T>& a, i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = a[l];
        } else {
            i64 m = l + (r - l) / 2;
            build(a, l, m, 2 * node + 1);
            build(a, m + 1, r, 2 * node + 2);
        }
    }

    T query(i64 l, i64 r, i64 tree_l, i64 tree_r, i64 node){
        i64 mid = tree_l + (tree_r - tree_l) / 2;
        if (tree_l == l && tree_r == r){
            return seg[node];
        } else if (r <= mid){
            return query(l, r, tree_l, mid, 2 * node + 1);
        } else if (l > mid){
            return query(l, r, mid + 1, tree_r, 2 * node + 2);
        } else {
            return query(l, mid, tree_l, mid, 2 * node + 1) + query(mid + 1, r, mid + 1, tree_r, 2 * node + 2);
        }
    }

    // sum update: add x to position p
    void update(i64 p, T x, i64 tree_l, i64 tree_r, i64 node){
        i64 mid = tree_l + (tree_r - tree_l) / 2;
        if (tree_l == p && p == tree_r){
            seg[node] = seg[node] + x;
        } else {
            if (p <= mid){
                update(p, x, tree_l, mid, 2 * node + 1);
            } else {
                update(p, x, mid + 1, tree_r, 2 * node + 2);
            }
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }
};

vector<i64> all_salaries;
vector<tuple<char, i64, i64>> queries;
vector<i64> arr;

void solve(){
    i64 n, q;
    cin >> n >> q;
    arr.resize(n);
    for (i64 i = 0; i < n; i++){
        cin >> arr[i];
        all_salaries.emplace_back(arr[i]);  // register salary
    }

    char mode;
    i64 a, b, k, x;
    for (i64 i = 0; i < q; i++){
        cin >> mode;
        if (mode == '!'){
            cin >> k >> x;
            queries.emplace_back(mode, --k, x);  // 0-INDEXING!
            all_salaries.emplace_back(x);  // register salary
        } else {
            cin >> a >> b;
            queries.emplace_back(mode, a, b);
        }
    }
    all_salaries.emplace_back((i64)2e18); // infinity
    sort(all_salaries.begin(), all_salaries.end());
    const i64 s = all_salaries.size();

    SumSegTree<i64> seg(vector<i64>(all_salaries.size(), 0), (i64)0);
    // add initial salaries
    for (i64 x: arr){
        i64 mapped_p = distance(all_salaries.begin(), lower_bound(all_salaries.begin(), all_salaries.end(), x));
        seg.update(mapped_p, (i64)1, 0, s - 1, 0);
    }

    for (auto[mode, x, y]: queries){
        if (mode == '!'){
            // find true salary pos
            i64 mapped_old = distance(all_salaries.begin(), lower_bound(all_salaries.begin(), all_salaries.end(), arr[x]));
            i64 mapped_new = distance(all_salaries.begin(), lower_bound(all_salaries.begin(), all_salaries.end(), y));
            arr[x] = y;
            seg.update(mapped_old, (i64)(-1), 0, s - 1, 0);
            seg.update(mapped_new, (i64)(+1), 0, s - 1, 0);
        } else {
            // contract range
            // if (y < all_salaries[0]){
            //     cout << 0 << endl;
            //     continue;
            // }
            // x = max(x, all_salaries[0]);

            vector<i64>::iterator left = lower_bound(all_salaries.begin(), all_salaries.end(), x);
            vector<i64>::iterator right = upper_bound(all_salaries.begin(), all_salaries.end(), y);
            i64 pl = distance(all_salaries.begin(), left);
            i64 pr = distance(all_salaries.begin(), --right);
            if (pl > pr){
                // this means the first position where >=x is also >y, so the [x,y] range does not intersect
                cout << 0 << endl;
            } else {
                i64 ans = seg.query(pl, pr, 0, s - 1, 0);
                cout << ans << endl;
            }
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
