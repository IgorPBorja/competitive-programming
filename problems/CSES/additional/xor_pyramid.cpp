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

constexpr i64 B = 40;

void solve(){
	i64 n;
	cin >> n;
	i64 a[n];
	i64 bits[B][n];
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
		for (i64 j = 0; j < B; j++){
			bits[j][i] = (a[i] & (1ll << j)) >> j;
		}
	}

	i64 v2s[n];
	v2s[0] = 0;
	for (i64 i = 1; i < n; i++) {
		v2s[i] = __builtin_ctz(i) + v2s[i - 1];
	}
	i64 ans = 0;
	for (i64 j = 0; j < B; j++){
		for (i64 i = 0; i < n; i++){
			i64 v2_choose = v2s[n - 1] - v2s[n - 1 - i] - v2s[i];
			if (v2_choose == 0){
				ans ^= (bits[j][i] << j);
			}
		}
	}
	cout << ans << endl;
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
