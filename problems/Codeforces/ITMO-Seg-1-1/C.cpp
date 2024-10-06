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

struct Node {
	i64 v = 0, cnt = 1;

	Node() {}
	Node(i64 v, i64 cnt) : v(v), cnt(cnt) {}
};

Node merge(Node n1, Node n2){
	if (n1.v < n2.v){
		return n1;
	} else if (n2.v < n1.v){
		return n2;
	} else {
		return Node(n1.v, n1.cnt + n2.cnt);
	}
}

struct SegMin {
	const static i64 MAXN = (i64)1e5 + 10; 
	Node seg[MAXN];
	const i64 n;

	SegMin(i64 a[], i64 n) : n(n){
		build(a, 0, n - 1, 0);
	}

	void build(i64 a[], i64 l, i64 r, i64 node){
		if (l == r){
			seg[node] = Node(a[l], 1);
		} else {
			const i64 m = l + (r - l) / 2;
			build(a, l, m, 2 * node + 1);
			build(a, m + 1, r, 2 * node + 2);
			seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
		}
	}

	Node _query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
		if (l == r && tl == tr){
			return seg[node];
		} else {
			const i64 tm = tl + (tr - tl) / 2;
			if (r <= tm){
				return _query(l, r, tl, tm, 2 * node + 1);
			} else if (l > tm){
				return _query(l, r, tm + 1, tr, 2 * node + 2);
			} else {
				return merge(
					_query(l, tm, tl, tm, 2 * node + 1),
					_query(tm + 1, r, tm + 1, tr, 2 * node + 2)
				);
			}
		}
	}

	pair<i64, i64> query(i64 l, i64 r){
		Node q = _query(l, r, 0, n - 1, 0);
		return {q.v, q.cnt};
	}

	void update(i64 p, i64 x, i64 tl, i64 tr, i64 node){
		if (tl == p && p == tr){
			seg[node] = Node(x, 1);
		} else {
			const i64 tm = tl + (tr - tl) / 2;
			if (p <= tm){
				update(p, x, tl, tm, 2 * node + 1);
			} else {
				update(p, x, tm + 1, tr, 2 * node + 2);
			}
			seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
		}
	}
};

void solve(){
	i64 n, m;
	cin >> n >> m;
	i64 a[n];
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}
	SegMin seg = SegMin(a, n);
	for (i64 i = 0; i < m; i++){
		i64 mode, p, v, l, r;
		cin >> mode;
		if (mode == 1){
			cin >> p >> v;
			--p;
			seg.update(p, v, 0, n - 1, 0);
		} else {
			cin >> l >> r;
			--l; --r;
			auto[vmin, cnt] = seg.query(l, r);
			cout << vmin << " " << cnt << endl;
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
