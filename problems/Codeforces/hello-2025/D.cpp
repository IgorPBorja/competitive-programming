#define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << " ";} cerr << endl;
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

const i64 INF = 2e18;

struct Node {
	i64 max_convenience;
	// left diff: a[x] - (x - left endpoint)
	// left sum: a[x] + (x - left endpoint)
	// right diff: a[x] + (right endpoint - x)
	// right sum: a[x] + (right endpoint - x)
	i64 max_left_diff, min_left_sum;
	i64 max_right_diff, min_right_sum;

	Node(
		i64 max_convenience,
		i64 max_left_diff,
		i64 min_left_sum,
		i64 max_right_diff,
		i64 min_right_sum
	) : max_convenience(max_convenience),
		max_left_diff(max_left_diff),
		min_left_sum(min_left_sum),
		max_right_diff(max_right_diff),
		min_right_sum(min_right_sum)
		{}

	Node(
		i64 value
	) : max_convenience(0),
		max_left_diff(value),  // a[x] - (x - x) = a[x]
		min_left_sum(value),  // a[x] - (x - x) = a[x]
		max_right_diff(value),  // a[x] + (x - x) = a[x]
		min_right_sum(value)  // a[x] + (x - x) = a[x]
		{}

	Node(){
		max_convenience = INF;
		max_left_diff = INF;
		min_left_sum = -INF;
		max_right_diff = INF;
		min_right_sum = -INF;
	}
};

ostream& operator<<(ostream& os, Node n){
	os << "C=" << n.max_convenience << "|maxLD=" << n.max_left_diff << "|minLD=" << n.min_left_sum
		<< "|maxRS=" << n.max_right_diff << "|minRS=" << n.min_right_sum;
	return os;
}

Node merge(
	Node left, Node right,
	i64 l, i64 m, i64 r
){
	i64 c = max(
		left.max_convenience,
		max(
			right.max_convenience,
			max(
				right.max_left_diff - left.min_right_sum - 1,
				left.max_right_diff - right.min_left_sum - 1
			)
		)
	);
	i64 max_left_diff = max(left.max_left_diff, right.max_left_diff - (m + 1 - l));
	i64 min_left_sum = min(left.min_left_sum, right.min_left_sum + (m + 1 - l));
	i64 max_right_diff = max(left.max_right_diff - (r - m), right.max_right_diff);
	i64 min_right_sum = min(left.min_right_sum + (r - m), right.min_right_sum);
	return Node(
		c,
		max_left_diff,
		min_left_sum,
		max_right_diff,
		min_right_sum
	);
}

struct ConvenienceSeg {
	i64 n;
	vector<i64> a;
	vector<Node> seg;

	ConvenienceSeg(const vector<i64> v) : n(v.size()), a(v) {
		seg.resize(4 * n);
		build(0, n - 1, 0);
	}

	void build(i64 l, i64 r, i64 node){
		if (l == r){
			seg[node] = Node(a[l]);  // 1-indexing positions
		} else {
			const i64 m = l + (r - l) / 2;
			build(l, m, 2 * node + 1);
			build(m + 1, r, 2 * node + 2);
			seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2], l, m, r);
		}
	}

	i64 _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
		if (l == tl && r == tr){
			return seg[node].max_convenience;
		} else {
			const i64 tm = tl + (tr - tl) / 2;
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

	void _update(i64 p, i64 x, i64 l, i64 r, i64 node){
		if (l == p && r == p){
			a[p] = x;
			seg[node] = Node(x);  // 1-indexing positions
		} else {
			const i64 m = l + (r - l) / 2;
			if (p <= m){
				_update(p, x, l, m, 2 * node + 1);
			} else {
				_update(p, x, m + 1, r, 2 * node + 2);
			}
			seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2], l, m, r);
		}
	}

	void update(i64 p, i64 x){
		_update(p, x, 0, n - 1, 0);
	}

	i64 query(){
		return _query(0, n - 1, 0, n - 1, 0);
	}
};

void solve(){
	i64 n, q;
	cin >> n >> q;
	vector<i64> a(n);
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	ConvenienceSeg seg(a);
	cout << seg.query() << endl;
	for (i64 i = 0; i < q; i++){
		i64 p, x;
		cin >> p >> x;
		--p;  // 0-index it!
		seg.update(p, x);
		cout << seg.query() << endl;
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
