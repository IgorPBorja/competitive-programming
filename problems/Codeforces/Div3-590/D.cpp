// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

struct SumSegTree {
    vector<int> seg;
    vector<int> a;
    int n;

    SumSegTree() {}
    SumSegTree(int n) : n(n) {
        seg.assign(4 * n, 0);
        a.assign(n, 0);
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
            seg[node] += x;
            a[p] += x;
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

void solve(){
    string s;
    cin >> s;
    i64 n = s.size();
    SumSegTree segs[26];
    for (i64 i = 0; i < 26; i++){
        segs[i] = SumSegTree(n);
    }
    for (i64 i = 0; i < n; i++){
        segs[s[i] - 'a'].update(i, +1);
    }

    i64 q;
    cin >> q;
    for (i64 i = 0; i < q; i++){
        i64 mode, pos, l, r;
        char c;
        cin >> mode;
        if (mode == 1){
            cin >> pos >> c;
            --pos;
            segs[s[pos] - 'a'].update(pos, -1);
            s[pos] = c;
            segs[s[pos] - 'a'].update(pos, +1);
        } else {
            cin >> l >> r;
            --l; --r;
            i64 distinct = 0;
            for (i64 c = 0; c < 26; c++) distinct += (segs[c].query(l, r) > 0);
            cout << distinct << endl;
        }
    }
}
 
signed main(){
	fastio;
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
