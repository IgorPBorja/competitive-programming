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
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 INF = 1e18;

struct MaxSegTree {
    vector<i64> seg;
    vector<i64> a;
    i64 n;

    MaxSegTree(i64 n, i64 val = -INF) : n(n) {
        seg.assign(4 * n, val);
        a.assign(n, val);
    }

    i64 query(i64 l, i64 r){
        return _query(l, r, 0, n - 1, 0);
    }

    void update(i64 p, i64 x){
        _update(p, x, 0, n - 1, 0);
    }

private:
    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr){
            return seg[node];
        } else {
            i64 tm = tl + (tr - tl) / 2;
            if (r <= tm){
                return _query(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm){
                return _query(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                return max(_query(l, tm, tl, tm, 2 * node + 1), _query(tm + 1, r, tm + 1, tr, 2 * node + 2));
            }
        }
    }

    void _update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
        if (tl == p && tr == p){
            seg[node] = x;
            a[p] = x;
        } else {
            i64 tm = tl + (tr - tl) / 2;
            if (p <= tm){
                _update(p, x, tl, tm, 2 * node + 1);
            } else {
                _update(p, x, tm + 1, tr, 2 * node + 2);
            }
            seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }
};

void solve(){
    i64 n;
    cin >> n;

    i64 h[n], s[n], b[n];
    for (i64 i = 0; i < n; i++){
        cin >> h[i];
        s[i] = h[i];
    }
    for (i64 i = 0; i < n; i++){
        cin >> b[i];
    }

    MaxSegTree dp(n, -INF);
    sort(s, s + n);
    // dp[i] = maximum sum of increasing subsequence ending at height s[i] using up to current loop position j
    // Transition: for iteration j putting i such that s[i] = h[j], 
    // dp[i] = max(1 <= i' <= i)dp[i'] + b[j]  (if the left term is not -INF)

    dp.update(lower_bound(s, s + n, h[0]) - s, b[0]);
    for (i64 j = 1; j < n; j++){
        i64 pos = lower_bound(s, s + n, h[j]) - s;
        i64 best_prefix = dp.query(0, pos);
        if (best_prefix != -INF){
            dp.update(pos, best_prefix + b[j]);
        } else {
            dp.update(pos, b[j]);  // use empty prefix
        }
    }
    cout << dp.query(0, n - 1) << endl;
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
