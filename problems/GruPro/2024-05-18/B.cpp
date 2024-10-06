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
	i64 x;
	cin >> x;

	vector<i64> d;
	while (x >= 1){
		d.emplace_back(x % (i64)10);
		x /= (i64)10;
	}
	reverse(d.begin(), d.end());

	for (i64 i = 0; i < d.size(); i++){
		if ((5 <= d[i]) && (d[i] < 9)){
			d[i] = 9 - d[i]; // 1...4
		} else if (i > 0 && d[i] == 9){
			d[i] = 0;
		}
	}
	
	i64 y = 0;
	i64 p10 = 1;
	for (i64 i = d.size() - 1; i >= 0; i--){
		y += p10 * d[i];
		p10 *= (i64)10;
	}
	cout << y << endl;
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
