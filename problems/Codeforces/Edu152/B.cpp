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
	i64 n, k;
	cin >> n >> k;
	pair<i64, i64> a[n];
	for (i64 i = 0; i < n; i++){
		cin >> a[i].first;
		a[i].first = (a[i].first % k == 0) ? k : a[i].first % k;
		a[i].second = i;
	}
	sort(a, a + n, [](pair<i64, i64> p1, pair<i64, i64> p2){
		return (p1.first > p2.first) || (p1.first == p2.first && p1.second < p2.second);
	});
	for (i64 i = 0; i < n; i++){
		cout << a[i].second + 1 << " ";
	}
	cout << endl;
}
 
signed main(){
	fastio;
// #ifdef DEBUG
// 	freopen("/tmp/in", "r", stdin);
// #endif
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
