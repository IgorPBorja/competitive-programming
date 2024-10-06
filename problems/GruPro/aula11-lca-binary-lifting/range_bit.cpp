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

struct RangeBIT {
	vector<i64> B1, B2;
	i64 n;

	RangeBIT(i64 n) : n(n) {
		B1.resize(n + 1);
		B2.resize(n + 1);
	}

	RangeBIT(const vector<i64> a) : n(a.size()) {
		B1.resize(n + 1);
		B2.resize(n + 1);
		for (i64 i = 0; i < n; i++){
			pt_update(i + 1, a[i]);
		}
	}

	// assumes 1-indexed
	i64 range_query(i64 l, i64 r){
		return pref(r) - pref(l - 1);	
	}

	// assumes 1-indexed
	void range_update(i64 l, i64 r, i64 x){
		raw_pt_update(l, x, B1);
		raw_pt_update(l, (l - 1) * x, B2);
		if (r + 1 <= n){
			raw_pt_update(r + 1, -x, B1);	
			raw_pt_update(r + 1, -r * x, B2);
		}
	}

	void pt_update(i64 p, i64 x){
		range_update(p, p, x);
	}
private:
	// assumes 1-indexed
	i64 pref(i64 m){
		i64 i = m;	
		i64 ans = 0;
		while (i >= 1){
			ans += B1[i] * m - B2[i];	
			i ^= i & -i;
		}
		return ans;
	}

	// assumes 1-indexed
	void raw_pt_update(i64 p, i64 x, vector<i64> &bit){
		i64 i = p;	
		while (i <= n){
			bit[i] += x;
			i += i & -i;
		}
	}
};

void solve(){
	// https://cses.fi/problemset/task/1735
	i64 n, q;
	cin >> n >> q;

	vector<i64> a(n);
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	RangeBIT bit(a);
	for (i64 i = 0; i < q; i++){
		i64 mode, a, b, u, k;
		cin >> mode;
		if (mode == 1){
			cin >> a >> b >> u;
			bit.range_update(a, b, u);
		} else {
			cin >> k;
			cout << bit.range_query(k, k) << endl;
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
