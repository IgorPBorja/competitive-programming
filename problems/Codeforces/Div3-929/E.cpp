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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

const i64 INF = 2e18;

void solve(){
	i64 n, q;
	
	cin >> n;
	i64 a[n + 1];
	for (i64 i = 0; i < n; i++){
		cin >> a[i + 1];
	}

	i64 p[n + 1];
	p[0] = 0;
	for (i64 i = 0; i < n; i++){
		p[i + 1] = p[i] + a[i + 1];
	}

	cin >> q;
	i64 l, u;
	for (i64 i = 0; i < q; i++){
		cin >> l >> u;
		// p[l] = a[1] + ... + a[l] (if a was 1-indexed)
		// with p[0] = 0 (empty sum)
		// we stop in the before the first x such that
		// (u - S[l,x-1]) + ... (u - S[l,x-1] - a[x] + 1) <= 0
		// <==> S[l,x - 1] + ... + S[l, x-1] + a[x] - 1 >= a[x] * u
		// <==> a[x] * (S[l, x - 1] - u) >= - a[x] * (a[x] - 1) / 2
		// <==> 2 * (u - S[l, x - 1]) <=  a[x] - 1

		// first position where segment is > value
		// so a[l] + ... + a[r] - 1 (last segment delta) >= u
		i64 r = upper_bound(p, p + n + 1, u + p[l - 1]) - p;
		// should we use a[r] still? only if 2 * (u - S[l,x-1]) > a[r] - 1
		// (i.e a[r] is small, not enough to create a negative OR ZERO resulting delta)
		// DROP if 2 * (u - S[l,x-1]) <= a[r] - 1
		if (r > l && a[r] - 1 >= (i64)2 * (u - p[r - 1] + p[l - 1])){
			--r;
		}
		cout << min(max(l, r), n) << " ";
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
