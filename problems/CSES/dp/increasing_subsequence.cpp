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

struct MaxSeg {
    vector<i64> seg;
    vector<i64> a;

    MaxSeg(i64 n){
        seg.assign(4 * n, 0);
        a.assign(n, 0);
    }

    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr){
            return seg[node];
        } else if (r <= tm){
            return _query(l, r, tl, tm, 2 * node + 1);
        } else if (l > tm){
            return _query(l, r, tm + 1, tr, 2 * node + 2);
        } else {
            return max(_query(l, tm, tl, tm, 2 * node + 1), _query(tm + 1, r, tm + 1, tr, 2 * node + 2));
        }
    }

    void _update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
        i64 tm = tl + (tr - tl) / 2;
        if (tl == p && p == tr){
            a[p] = x;
            seg[node] = x;
        } else if (p <= tm){
            _update(p, x, tl, tm, 2 * node + 1);
            seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
        } else {
            _update(p, x, tm + 1, tr, 2 * node + 2);
            seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    i64 query(i64 l, i64 r){
        const i64 n = a.size();
        return _query(l, r, 0, n - 1, 0);
    }

    void update(i64 p, i64 x){
        const i64 n = a.size();
        return _update(p, x, 0, n - 1, 0);
    }
};

void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    vector<pair<i64, i64>> elem(n);
    for (i64 i = 0; i < n; i++){
        elem[i] = make_pair(a[i], i);
    }
    sort(elem.begin(), elem.end());
    MaxSeg s(n);

    i64 ans = 0;
    for (i64 i = 0; i < n; i++){
        // find FIRST ocurrence of a[i] 
        // since has to ignore all equals, as the sequence must be strictly increasing
        i64 p = lower_bound(elem.begin(), elem.end(), make_pair(a[i], (i64)0)) - elem.begin() - 1;
        i64 cur = lower_bound(elem.begin(), elem.end(), make_pair(a[i], i)) - elem.begin();
        if (p < 0){
            // is first ocurrence of array minimum
            ans = max(ans, (i64)1);
            s.update(cur, 1);
        } else {
            i64 partial = 1 + s.query(0, p);
            ans = max(ans, partial);
            s.update(cur, partial);
        }
    }
    cout << ans << endl;
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
