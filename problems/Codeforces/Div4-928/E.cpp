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

i64 cnt_v2(i64 upper, i64 pot){
	// (2k + 1) * pot <= upper ==> 2k + 1 <= (upper / pot) ==> 2k + 1 <= floor(upper / pot)
	// ==> k <= floor((floor(upper / pot) - 1) / 2)
	// we want k + 1, of course
	if (pot > upper) return 0;
	return 1 + ((upper / pot) - 1) / 2;
}

void solve(){
	i64 n, k;
	cin >> n >> k;
	i64 pot = 1, cur = 0;
	while (cur + cnt_v2(n, pot) < k){
		cur += cnt_v2(n, pot);
		pot *= (i64)2;
	}
	i64 diff;
	if (pot == 1){
		diff = k; // k is really small, odd only already covers	
	} else {
		diff = (k - cur);
	}
	cout << pot * (2 * (diff - 1) + 1) << endl;
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
