#define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
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

const i64 INF = 1e9;


struct SumSeg {
    vector<i64> seg;
    i64 n;

    SumSeg(i64 n) : n(n) {
        seg.assign(4 * n, 0);
    }

    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr) return seg[node];
        else {
            const i64 tmid = tl + (tr - tl) / 2;
            if (r <= tmid) return _query(l, r, tl, tmid, 2 * node + 1);
            else if (l > tmid) return _query(l, r, tmid + 1, tr, 2 * node + 2);
            else return _query(l, tmid, tl, tmid, 2 * node + 1) + _query(tmid + 1, r, tmid + 1, tr, 2 * node + 2);
        }
    }

    void _add(i64 p, i64 delta, i64 tl, i64 tr, i64 node){
        if (tl == p && p == tr){
            seg[node] += delta;
        } else {
            const i64 tmid = tl + (tr - tl) / 2;
            if (p <= tmid) _add(p, delta, tl, tmid, 2 * node + 1);
            else _add(p, delta, tmid + 1, tr, 2 * node + 2);

            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }

    i64 query(i64 l, i64 r) {
        return _query(l, r, 0, n - 1, 0);
    }

    void add(i64 p, i64 x){
        _add(p, x, 0, n - 1, 0);
    }
};

/*
movement = transpositions to original position after sorting in increasing order!
*/
i64 original_moved(vector<i64> a){

    /*
    Let p[1]...p[k] be the positions of all values >= c in increasing order

    Then shifts are n-1-p[k] + n-2-p[k-1] + ...
    which is some constant - sum of positions
    */
    const i64 n = a.size();

    set<i64> _distinct;
    map<i64, vector<i64>> pos;
    for (i64 i = 0; i < n; i++) {
        _distinct.insert(a[i]);
        pos[a[i]].emplace_back(i);
    }
    vector<i64> distinct;
    distinct.emplace_back(0);
    for (i64 x: _distinct) distinct.emplace_back(x);

    i64 delta = 0;
    i64 pos_sum = 0, pos_cnt = 0;
    for (i64 i = (i64)distinct.size() - 1; i >= 1; i--){
        i64 cur = distinct[i];  // 
        i64 prev = distinct[i - 1];
        for (i64 p: pos[cur]){
            ++pos_cnt;
            pos_sum += p;
        }
        // n-1..n-pos_cnt ==> (n-1)n/2 - (n-pos_cnt-1)*(n-pos_cnt)/2
        i64 x = ((n-1) * n)/2 - ((n-pos_cnt-1)*(n-pos_cnt))/2 - pos_sum;
        delta += (cur - prev) * x;
    }
    return delta;
}

void solve(){
    /*
    Let C[i][k] be the count of positions j before i where a[j] >= k
    the benefit from decreasing a[i] is
    * 1 more shift distance for each stack a[j] >= a[i] where j < i, that is, C[i][a[i]].
    * minus the distance that the removed block would travel, which is just
        |i+1...n-1| - cnt of geq values to the right = n-1-i - cnt of geq values to the right
    
    
    Let R[i][r] be the amount of blocks on row r on columns i+1..n-1
    These blocks occupy positions n-1..n-R[i][r]
    The block at column i and row r will travel to position n-R[i][r]-1 ==>
        dist = |n-R[i][r]-1-i| = |n-1-i-R[i][r]|
    
    
    We can build C as a 1D array C[k=0..n] incrementally:
        each new processed value a[j] contributes to 1..a[j]
        we can use a lazy seg for these updates? overkill?

    Maybe we can process in order of (a[i], i) instead, and avoid the lazy seg
    */

    i64 n;
    cin >> n;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];

    auto base = original_moved(a);

    SumSeg right_cnt(n + 1);
    vector<i64> individual_delta(n);

    for (i64 i = n - 1; i >= 0; i--){
        if (i + 1 < n){
            right_cnt.add(a[i + 1], 1);
        }
        individual_delta[i] = n - 1 - i - right_cnt.query(a[i], n);
    }


    SumSeg left_cnt(n + 1);
    vector<i64> affected_before(n);
    for (i64 i = 0; i < n; i++){
        if (i > 0){
            left_cnt.add(a[i - 1], 1);
        }
        affected_before[i] = left_cnt.query(a[i], n);
    }
    i64 best_delta = 0;

    // print("individual_delta=", individual_delta);
    // print("affected_before=", affected_before);
    for (i64 i = 0; i < n; i++){
        best_delta = max(best_delta, affected_before[i] - individual_delta[i]);
    }

    cout << base + best_delta << endl;
}
 
signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--){
		solve();
	}
}
