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

i64 op(i64 x){ // O(log x)
	i64 bits[31];
	for (i64 i = 0; i < 31; i++){
		bits[30 - i] = 1 - (x % 2);
		x /= (i64)2;
	}
	i64 y = 0, pot = 1;
	for (i64 i = 30; i >= 0; i--){
		y += pot * bits[i];
		pot *= (i64)2;
	}
	return y;
}

void solve(){
	i64 n;
	i64 x;
	cin >> n;
	map<i64, i64> cnt;
	for (i64 i = 0; i < n; i++){
		cin >> x;
		++cnt[x];
	}

	i64 g = 0;
	for (auto[x, c]: cnt){
		g += c;
		cnt[op(x)] = max(cnt[op(x)] - c, (i64)0);
	}
	cout << g << endl;
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
