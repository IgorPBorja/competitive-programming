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

void solve(){
	// leaving only two pieces
	// u' = (-1)^{n - 2} u mod 2
	// d' = d mod 2
	i64 n, u = 0, d = 0;
	string s;
	cin >> n;
	cin >> s;

	for (i64 i = 0; i < n; i++){
		if (s[i] == 'U') ++u;
		else ++d;
	}

	i64 winning;
	i64 cur = (n % 2);  // who comes after removing the (n-2)th
	if (n % 2 == 0){
		// then u'=u, d'=d
		if (u % 2 == 0){
			// either UU or DD
			winning = 1 - cur;
		} else {
			// UD or DU
			winning = cur;
		}
	} else {
		// then u' = 1 - u, d'=d
		if (u % 2 == 0){  // then d % 2 == 1
			// either UD or DU
			winning = cur;
		} else { // then d % 2 == 0
			// either DD or UU
			winning = 1 - cur;
		}
	}
	if (winning == 0){
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
