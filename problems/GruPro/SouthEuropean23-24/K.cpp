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

/*
if we keep the position in a seg
then we can use a lazy seg 
and removing element at node x with position p
amounts to subtracting 1 to everyone after p

we do it differently
start with ones array, find position and subtract one at position + 1
then the last index i with pref(i) == k is the one currently at position k

we can use an iterative seg and bitmasks
and do bsearch. each time we try to add 2^b from B-1...0 to the idx

if we have bits i1,...,ik active then we took a right at i1...ik
*/

// TODO CHANGE
const i64 B = 22;
i64 seg[4 * (1ll << B)];

void build(i64 l, i64 r, i64 node){
	// cerr << "entering at node=" << node << endl;
	if (l == r){
		seg[node] = 1;
	} else {
		const i64 m = l + (r - l) / 2;
		build(l, m, 2 * node + 1);
		build(m + 1, r, 2 * node + 2);
		seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
	}
}

void update(i64 tp, i64 tl, i64 tr, i64 node){
	if (tl == tp && tp == tr){
		--seg[node];
	} else {
		const i64 tm = tl + (tr - tl) / 2;
		if (tp <= tm){
			update(tp, tl, tm, 2 * node + 1);
		} else {
			update(tp, tm + 1, tr, 2 * node + 2);
		}
		seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
	}
}

i64 query(i64 l, i64 r, i64 tl, i64 tr, i64 node){
	if (l == tl && r == tr){
		return seg[node];
	} else {
		const i64 tm = tl + (tr - tl) / 2;
		if (r <= tm){
			return query(l, r, tl, tm, 2 * node + 1);
		} else if (l > tm){
			return query(l, r, tm + 1, tr, 2 * node + 2);
		} else {
			return query(l, tm, tl, tm, 2 * node + 1) + query(tm + 1, r, tm + 1, tr, 2 * node + 2);	
		}
	}
}

void printpref(){
	cerr << "orig: ";
	for (i64 i = 0; i < (1ll << B); i++){
		cout << i + 1 << " ";
	}
	cout << endl;
	cerr << "seg : ";
	for (i64 i = 0; i < (1ll << B); i++){
		cerr << query(0, i, 0, (1ll << B) - 1, 0) << " ";
	}
	cerr << endl;
}

i64 idx(i64 k){
	i64 l = 0, r = (1ll << B) - 1;
	i64 ans;
	i64 node = 0;
	i64 cur = 0;
	for (i64 i = B - 1; i >= 0; i--){
		// trying to take a right from node
		i64 m = l + (r - l) / 2;
		if (cur + seg[2 * node + 1] <= k){
			ans = m;
			l = m + 1;
			cur += seg[2 * node + 1];
			node = 2 * node + 2;
		} else {
			r = m;
			node = 2 * node + 1;
		}
	}
	return ans;
}

void solve(){
	build(0, (1ll << B) - 1, 0);

	i64 n;
	cin >> n;
	i64 a[n];
	for (i64 i = 0; i < n / 2; i++){
		cin >> a[2 * i];
	}
	for (i64 i = 0; i < n / 2; i++){
		cin >> a[2 * i + 1];
	}
	
	vector<i64> t[2];
	// printpref();
	for (i64 i = 0; i < n; i++){
		i64 j = idx(a[i]);
		// cout << "for pos=" << a[i] << " found j=" << j + 1 << endl;
		t[i % 2].emplace_back(j + 1);
		update(j + 1, 0, (1ll << B) - 1, 0);
		// printpref();
	}

	for (i64 i = 0; i < 2; i++){
		for (auto x: t[i]){
			cout << x << " ";
		}
		cout << endl;
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
