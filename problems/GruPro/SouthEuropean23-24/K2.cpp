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

// TODO CHANGE
const i64 MAXN = (i64)4e6 + 10;
i64 seg[4 * MAXN];

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

// search for first idx with k-value
i64 idx(i64 k, i64 tl, i64 tr, i64 node){
    if (tl == tr){
        return tl;
    }
    const i64 tm = tl + (tr - tl) / 2;
    if (seg[2 * node + 1] >= k){
        // there is enough to fill on the left, so stay left (conservative approach, will find first occurence)
        return idx(k, tl, tm, 2 * node + 1);
    } else {
        // discard first half and search right
        // by invariant k - seg[2 * node + 1] > 0 here always
        return idx(k - seg[2 * node + 1], tm + 1, tr, 2 * node + 2);
    }
}

void solve(){
	build(0, MAXN - 1, 0);

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
	for (i64 i = 0; i < n; i++){
		i64 j = idx(a[i], 0, MAXN - 1, 0);
		t[i % 2].emplace_back(j + 1);
		update(j, 0, MAXN - 1, 0);
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

