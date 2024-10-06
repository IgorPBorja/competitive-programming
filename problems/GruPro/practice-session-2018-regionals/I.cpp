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
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

struct MaxAbsSeg {
    vector<i64> seg;
    vector<i64> a;
    const i64 n;

    MaxAbsSeg(const vector<i64> &a) : n(a.size()) {
        seg.resize(4 * n);
        this->a.resize(n);
        copy(a.begin(), a.end(), this->a.begin());
        build(0, n - 1, 0);
    }

    void build(i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = (l > 0) ? abs(a[l] - a[l - 1]) : 0;
        } else {
            const i64 m = l + (r - l) / 2;
            build(l, m, 2 * node + 1);
            build(m + 1, r, 2 * node + 2);
            seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    i64 range_max(i64 l, i64 r){
        if (l > r){
            return 0;
        } else {
            return query(l, r, 0, n - 1, 0);
        }
    }

    void update(i64 p, i64 x){
        // sets a[p] = x
        a[p] = x;
        // update backwards diff
        if (p > 0){
            _update(p, abs(a[p] - a[p - 1]), 0, n - 1, 0);
        }
        // update forwards diff
        if (p + 1 < n){
            _update(p + 1, abs(a[p + 1] - a[p]), 0, n - 1, 0);
        }
    }
private:
    i64 query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        const i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr){
            return seg[node];
        } else if (r <= tm){
            return query(l, r, tl, tm, 2 * node + 1);
        } else if (l > tm){
            return query(l, r, tm + 1, tr, 2 * node + 2);
        } else {
            return max(query(l, tm, tl, tm, 2 * node + 1), query(tm + 1, r, tm + 1, tr, 2 * node + 2));
        }
    }

    void _update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
        if (tl == p && p == tr){
            seg[node] = x;
        } else {
            const i64 tm = tl + (tr - tl) / 2;
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
    i64 n, q;
    cin >> n >> q;

    vector<i64> h(n);
    for (i64 i = 0; i < n; i++){
        cin >> h[i];
    }

    MaxAbsSeg seg(h);
    for (i64 j = 0; j < q; j++){
        i64 mode, i, H;
        cin >> mode >> i >> H;
        --i;
        if (mode == 1){
            seg.update(i, H);
        } else {
            i64 final = 1;  // i itself
            // binary search to the left
            // for min(j <= i: max(j...i)abs(h[j] - h[j - 1]) <= H)
            i64 l = 0, r = i + 1, ans = i + 1;
            while (l <= r){
                const i64 m = l + (r - l) / 2;
                const i64 val = seg.range_max(m, i);
                if (val <= H){
                    ans = m;
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            final += (i - max(ans - 1, (i64)0));  // max(j - 1, 0) ... i - 1 ==> i - max(ans - 1, 0)

            // binary search to the right
            // for max(j >= i: max(i + 1...j)abs(h[j] - h[j - 1]) <= H)
            l = i, r = n - 1, ans = i;
            while (l <= r){
                const i64 m = l + (r - l) / 2;
                const i64 val  = seg.range_max(i + 1, m);
                if (val <= H){
                    ans = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            final += ans - i;  // i + 1 ... j ==> j - i
            cout << final << endl;
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
