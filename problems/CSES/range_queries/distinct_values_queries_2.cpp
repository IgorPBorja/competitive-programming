// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
#include <tuple>
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

struct SegTree {
    vector<i64> seg;

    SegTree(i64 n){
        vector<i64> a(n, 0);
        seg.resize(4 * n);
        build(a, 0, n - 1, 0);
    }

    SegTree(vector<i64> a){
        seg.resize(4 * a.size());
        build(a, 0, a.size() - 1, 0);
    }

    void build(vector<i64> &a, i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = a[l];
        } else {
            i64 m = l + (r - l) / 2;
            build(a, l, m, 2 * node + 1);
            build(a, m + 1, r, 2 * node + 2);
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }

    void pt_update(i64 p, i64 delta, i64 tl, i64 tr, i64 node){
        if (tl == p && p == tr){
            seg[node] += delta;
        } else {
            i64 m = tl + (tr - tl) / 2;
            if (p <= m){
                pt_update(p, delta, tl, m, 2 * node + 1);
            } else if (p > m){
                pt_update(p, delta, m + 1, tr, 2 * node + 2);
            }
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }

    i64 query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr){
            return seg[node];
        } else {
            i64 m = tl + (tr - tl) / 2;
            if (r <= m){
                return query(l, r, tl, m, 2 * node + 1);
            } else if (l > m){
                return query(l, r, m + 1, tr, 2 * node + 2);
            } else {
                return query(l, m, tl, m, 2 * node + 1) + query(m + 1, r, m + 1, tr, 2 * node + 2);
            }
        }
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;

    map<i64, i64> after_last_pos; // i-th entry ==> (last position where element i was found) + 1
    i64 a[n];
    tuple<i64, i64, i64> queries[q];
    i64 answers[q];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    for (i64 i = 0; i < q; i++){
        i64 l, r;
        cin >> l >> r;
        --l; --r;  // NOTE: 0-INDEX
        queries[i] = make_tuple(l, r, i);
    }
    sort(queries, queries + q, [](tuple<i64, i64, i64> a, tuple<i64, i64, i64> b){
        return (get<1>(a) < get<1>(b)) || (get<1>(a) == get<1>(b) && get<0>(a) < get<0>(b));
    });
    // cerr << "input OK" << endl;

    i64 cur_r = -1;
    SegTree seg(n);
    for (i64 i = 0; i < q; i++){
        i64 l = get<0>(queries[i]), r = get<1>(queries[i]);
        if (r > cur_r){
            for (i64 j = cur_r + 1; j <= r; j++){
                if (after_last_pos[a[j]] > 0){  // was already there
                    seg.pt_update(after_last_pos[a[j]] - 1, -1, 0, n - 1, 0);
                }
                seg.pt_update(j, +1, 0, n - 1, 0);
                after_last_pos[a[j]] = j + 1;
                // cerr << "OK" << endl;
            }
            cur_r = r;
        }
        answers[get<2>(queries[i])] = seg.query(l, r, 0, n - 1, 0);
    }

    for (i64 i = 0; i < q; i++){
        cout << answers[i] << endl;
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
