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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

void solve(){
	i64 n, q;
	cin >> n >> q;

	vector<i64> uses(n, 0);
	vector<i64> a(n);
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	for (i64 i = 0; i < q; i++){
		i64 l, r;
		cin >> l >> r;
		--l; --r;
		++uses[l];
		if (r + 1 < n){
			--uses[r + 1];
		}
	}

	// prefix sum
	for (i64 i = 1; i < n; i++){
		uses[i] += uses[i - 1];
	}

	// rearrangement inequality: max sum in same-order matching
	sort(uses.begin(), uses.end());
	sort(a.begin(), a.end());

	i64 m = 0;
	for (i64 i = 0; i < n; i++){
		m += a[i] * uses[i];
	}
	cout << m << endl;
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
