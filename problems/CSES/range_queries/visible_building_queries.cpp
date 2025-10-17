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

/*
Each segtree node stores:
* the range max
* the ordered list of heights for the visible buildings for that range

Note that the range max is **always visible**.

A building a[i] is visible in [l,r] if a[i] > max(a[l..i-1]). So we get a sequence
a[p[1]] = a[l] < ... < a[p[k]]
and, even more strongly, a[p[i]] > max(a[l..p[i]-1])

We store a vector of (value, position) pairs of visible buildings.
Notice that if (x, i) comes before (y, j) then both i < j and x < y
by the visibility condition

So given two lists, left and right, to merge
we can do binary search to find how many buildings in the right visible list
are actually visible when incorporating the left list

More generally, given two nodes L = Range(tl, tm) and R = Range(tm+1,tr), to query
[l,r] with l < tm < r we take the number of visible elements and range max over [l, tm],
say k and M, and then binary search for the first element in R with has value > M, at p
and the first with index > r, at q, and do q - p
*/

const i64 INF = (i64)2e18;

struct Node {
    vector<i64> visible;
    vector<i64> visible_pos;
    i64 M;

    Node() : M(-INF) {}
    Node(i64 i, i64 x) {
        visible.emplace_back(x);
        visible_pos.emplace_back(i);
        M = x;
    }
    Node(const Node& other){
        visible = other.visible;
        visible_pos = other.visible_pos;
        M = other.M;
    }

    // we must have x > M
    void add(i64 i, i64 x){
        visible.emplace_back(x);
        visible_pos.emplace_back(i);
        M = x;
    }

    void operator=(const Node& other){
        visible = other.visible;
        visible_pos = other.visible_pos;
        M = other.M;
    }
};

struct VisibleSeg {
    vector<Node> seg;
    const vector<i64> a;
    i64 n;

    VisibleSeg(const vector<i64>& a) : a(a), n(a.size()) {
        seg.resize(4 * n);
        build(0, n - 1, 0);
    }

    // O(N log^2 N) build
    void build(i64 l, i64 r, i64 node){
        if (l == r){
            seg[node] = Node(l, a[l]);
        } else {
            const i64 m = l + (r - l) / 2;
            build(l, m, 2 * node + 1);
            build(m + 1, r, 2 * node + 2);
            seg[node] = Node(seg[2 * node + 1]);

            i64 left_max = seg[2 * node + 1].M;
            auto it = upper_bound(all(seg[2 * node + 2].visible), left_max);
            for (; it != seg[2 * node + 2].visible.end(); it++){
                i64 j = it - seg[2 * node + 2].visible.begin();
                i64 value = *it;
                i64 idx = seg[2 * node + 2].visible_pos[j];
                seg[node].add(idx, value);
            }
        }
    }

    // pair (max, visible buildings)
    pair<i64, i64> _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
        if (l == tl && r == tr){
            return make_pair(seg[node].M, seg[node].visible.size());
        } else {
            const i64 tm = tl + (tr - tl) / 2;
            if (r <= tm){
                return _query(l, r, tl, tm, 2 * node + 1);
            } else if (l > tm) {
                return _query(l, r, tm + 1, tr, 2 * node + 2);
            } else {
                auto[left_max, c1] = _query(l, tm, tl, tm, 2 * node + 1);
                i64 s = upper_bound(all(seg[2 * node + 2].visible), left_max) - seg[2 * node + 2].visible.begin();
                i64 e = upper_bound(all(seg[2 * node + 2].visible_pos), r) - seg[2 * node + 2].visible_pos.begin();
                // all buildings in the right visible building list
                // between index s and e-1 (inclusive) are visible
                i64 c = c1 + max(e - s, (i64)0);
                i64 M = (e > s ? seg[2 * node + 2].visible[e - 1] : left_max);
                return make_pair(M, c);
            }
        }
    }

    pair<i64, i64> query(i64 l, i64 r) { return _query(l, r, 0, n - 1, 0); }
};

void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> h(n);
    for (i64 i = 0; i < n; i++) cin >> h[i];

    VisibleSeg seg(h);
    for (i64 i = 0; i < q; i++){
        i64 l, r;
        cin >> l >> r;
        --l; --r;
        auto[_, c] = seg.query(l, r);
        cout << c << endl;
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
