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
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

/*
we calculate the inverse permutation
q[i] = position of i in p
(i.e such that p[q[i]] = i). So given a integer 1 <= x <= n,
the next number after x in permutation p (seen as a cycle) if p[(q[x] + 1) mod n]

Then we calculate an array of vectors pos[1..n]
where pos[i] are all the 0 <= j < m such that a[j] = i (the positions of i in the array)

then for each 0 <= i < m position in the array, we define
f(i) = min(i < j < m: a[j] = p[(q[a[i]] + 1) mod n]) = lower bound of i in pos[p[(q[a[i]] + 1) mod n]]
the position of the first appearence of the next permutation item after i in the array a.
We define it as INF if the next permutation item does not appear anymore after it, and we define f(INF) = INF
for consistency.

Then f^n(i) is the first position where we can complete a cyclic shift starting from position i

For each query [l, r] we want to know if min(l <= i <= r)f^n(i) <= r

1. Calculate q, pos
2. Use binary lifting in f
3. Calculate array [f^n(x) for x=0...m-1]
4. Build min segtree on top of it
*/

struct StaticMinSeg {
    vector<i64> seg;
    i64 n;

    StaticMinSeg(const vector<i64> &a) : n(a.size()) {
        seg.resize(4 * n);
        build(0, n - 1, 0, a);
    }

    i64 query(i64 l, i64 r){
        return _query(l, r, 0, n - 1, 0);
    }
private:
    void build(i64 l, i64 r, i64 node, const vector<i64> &a){
        if (l == r){
            seg[node] = a[l];
        } else {
            const i64 m = l + (r - l) / 2;
            build(l, m, 2 * node + 1, a);
            build(m + 1, r, 2 * node + 2, a);
            seg[node] = min(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        const i64 tm = tl + (tr - tl) / 2;
        if (l == tl && r == tr){
            return seg[node];
        } else if (r <= tm){
            return _query(l, r, tl, tm, 2 * node + 1);
        } else if (l > tm){
            return _query(l, r, tm + 1, tr, 2 * node + 2);
        } else {
            return min(
                _query(l, tm, tl, tm, 2 * node + 1),
                _query(tm + 1, r, tm + 1, tr, 2 * node + 2)
            );
        }
    }
};

void solve(){
    i64 n, m, num_queries;
    cin >> n >> m >> num_queries;

    i64 p[n], q[n], a[m];
    vector<i64> pos[n];
    for (i64 i = 0; i < n; i++){
        cin >> p[i];
        --p[i];
        q[p[i]] = i;
    }
    for (i64 i = 0; i < m; i++){
        cin >> a[i];
        --a[i];
        pos[a[i]].emplace_back(i);
    }

    i64 ilog = 0;
    while ((1ll << (ilog + 1)) <= m) ++ilog;

    vector<vector<i64>> f(ilog + 1, vector<i64>(m, INF));
    for (i64 i = 0; i < m; i++){
        i64 next_val = p[(q[a[i]] + 1) % n];
        auto it = lower_bound(pos[next_val].begin(), pos[next_val].end(), i);
        if (it != pos[next_val].end()){
            f[0][i] = *it;
        }
    }

    for (i64 i = 1; i <= ilog; i++){
        for (i64 j = 0; j < m; j++){
            if (f[i - 1][j] != INF){
                f[i][j] = f[i - 1][f[i - 1][j]];
            } else {
                f[i][j] = INF;
            }
        }
    }

    auto jump = [&f, ilog](i64 pos, i64 k){
        for (i64 i = 0; i <= ilog && pos != INF; i++){
            if ((k >> i) & 1){
                pos = f[i][pos];
            }
        }
        return pos;
    };

    vector<i64> shift_end(m);
    for (i64 i = 0; i < m; i++){
        shift_end[i] = jump(i, n - 1);
    }

    // build seg tree
    StaticMinSeg seg(shift_end);
    
    for (i64 i = 0; i < num_queries; i++){
        i64 l, r;
        cin >> l >> r;
        --l; --r;
        i64 first_shift_end = seg.query(l, r);
        if (first_shift_end <= r){
            cout << 1;
        } else {
            cout << 0;
        }
    }
    cout << endl;
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
