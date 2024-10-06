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

/*
a = 2x[1] - 1 + ... 2x[k] - 1
<==> (a + k) / 2 = x[1] + ... + x[k] where x[1] ... x[k] are distinct positive

take 1 + 2 + ... + k - 1 + x (remainder

==> needs (a + k) / 2 >= 1 + 2 + ... + k = k(k + 1) / 2
<==> a + k >= k (k + 1) <==> a >= k^2

Also a must be k mod 2
*/

void solve(){
	i64 n, k;
	cin >> n >> k;
	if (n >= k * k && (n % 2 == k % 2)){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
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
