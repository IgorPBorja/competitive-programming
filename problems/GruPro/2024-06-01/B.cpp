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
	cin >> n;

	i64 a[n], p[n];
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}
	// pile i starts at p[i]
	// p[n - 1] = a[0] + ... + a[n - 2]
	p[0] = 0;
	for (i64 i = 1; i < n; i++){
		p[i] = p[i - 1] + a[i - 1];
	}

	cin >> q;
	i64 x;
	for (i64 i = 0; i < q; i++){
		// from 0 to a[0] + ... + a[n - 1] - 1
		// we want max(p[i] | p[i] <= x) = min(p[i] | p[i] > x) - 1
		cin >> x;
		--x; // 0-index
		// naturally y > 0 since x >= 0
		// and y <= n
		i64 y = upper_bound(p, p + n, x) - p;
		cout << y << endl;
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
