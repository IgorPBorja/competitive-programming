#define TESTCASES
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

void solve(){
	i64 n, q;
	cin >> n >> q;
	i64 x[n];
	for (i64 i = 0; i < n; i++){
		cin >> x[i];
	}

	// suppose wlog x is in increasing order
	// NOTE: all x values are unique
	// so for x[i] we can have any of the 0..i as left anchors and all the i+1..n-1 as right anchors
	// ==> each point in x[i]+1...x[i + 1] - 1 is in (i + 1) * (n - 1 - i) segments
	// and x[i] is in i * (n - 1 - i) + i + (n - 1 - i) segments
	// and x[n - 1] is in n - 1 segments

	map<i64, i64> cnt; // cnt[k] elements in exactly k segments
	for (i64 i = 0; i + 1 < n; i++){
		cnt[(i + 1) * (n - 1 - i)] += x[i + 1] - x[i] - 1;
		++cnt[i * (n - 1 - i) + i + (n - 1 - i)];
	}
	++cnt[n - 1];

	i64 k;
	for (i64 i = 0; i < q; i++){
		cin >> k;
		cout << cnt[k] << " ";
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
