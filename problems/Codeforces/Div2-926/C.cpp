#define TESTCASES
 
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
	i64 k, x, a;
	cin >> k >> x >> a;

	i64 cur = 0;
	for (i64 i = 0; i < x; i++){
		// has lost cur
		// must win at least cur + 1 ==> bet * (k - 1) >= (cur + 1)
		// ==> bet = ceil((cur + 1) / (k - 1)) = floor((cur + 1 + k - 1 - 1) / (k - 1))
		i64 bet = ((cur + k - 1) / (k - 1));
		cur += bet;
		if (a < cur){
			cout << "NO" << endl;
			return;
		}
	}
	// lost all x, will win now
	i64 final_bet = ((cur + k - 1) / (k - 1));
	if (a >= cur + final_bet){
		// will win at least 1
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}

}
 
signed main(){
	fastio;
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
