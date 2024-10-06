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

struct ArgmaxSuffixSeg {
    vector<i64> seg;
    vector<i64> suf;
    
    ArgmaxSuffixSeg(i64 s[], i64 n){
        seg.resize(4 * n);
        suf.resize(n);
        suf[n - 1] = s[n - 1];
        for (i64 i = n - 2; i >= 0; i--){
            suf[i] = suf[i + 1] + s[i];
        }
        _build(0, n - 1, 0);
    }
    
    void _build(i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = l;
        } else {
            i64 m = l + (r - l) / 2;
            _build(l, m, 2 * node + 1);
            _build(m + 1, r, 2 * node + 2);
        
            i64 idx_l = seg[2 * node + 1], idx_r = seg[2 * node + 2];
            if (suf[idx_l] >= suf[idx_r]){
                seg[node] = idx_l;
            } else {
                seg[node] = idx_r;
            }
        }
    }
    
    i64 _argmax_query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr){
            return seg[node];
        } else if (r <= tm){
            return _argmax_query(l, r, tl, tm, 2 * node + 1);
        } else if (l > tm){
            return _argmax_query(l, r, tm + 1, tr, 2 * node + 2);
        } else {
            i64 idx_l = _argmax_query(l, tm, tl, tm, 2 * node + 1);
            i64 idx_r = _argmax_query(tm + 1, r, tm + 1, tr, 2 * node + 2);
            if (suf[idx_l] >= suf[idx_r]){
                return idx_l;
            } else {
                return idx_r;
            }
        }
    }

    i64 argmax_query(i64 l, i64 r){
        const i64 n = suf.size();
        return _argmax_query(l, r, 0, n - 1, 0);
    }
};

void solve(){
    // for i = n-1...0
    // grab the best suffix starting after i
    // => suffix max of suffixes
    
    i64 n, k;
    cin >> n >> k;
    
    i64 a[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    
    ArgmaxSuffixSeg seg(a, n);
    vector<i64> p(k + 1);
    p[k] = n;
    for (i64 i = k - 1; i >= 0; i--){
        // i-th start point is argmax(s[j] - s[p[i + 1]]: i <= j < p[i + 1]) = argmax(s[j]: i <= j < p[i + 1])
        p[i] = seg.argmax_query(i, p[i + 1] - 1);
    }
    
    // print(p);
    // cerr << "OK" << endl;
    
    i64 cur = 0;
    i64 cost = 0;
    for (i64 i = 0; i < n; i++){
        if (i >= p[cur + 1]){
            ++cur;
        }
        cost += a[i] * (cur + 1);
    }
    cout << cost << endl;
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
