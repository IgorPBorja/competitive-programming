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
	map<i64, pair<i64, i64>> m;
	i64 n;
	cin >> n;
	vector<pair<i64, i64>> a(n);
	for (i64 i = 0; i < n; i++){
		a[i] = make_pair(0, i);
	}

	i64 x;
	for (i64 i = 0; i < n; i++){
		cin >> x;
		++a[x].first;
	}

	vector<i64> dp(n);
	bool ok = true;
	for (i64 i = 0; i < n; i++){
		if (ok && a[i].first == 1){
			ok = false;
			continue;
		}
		if (a[i].first == 0 || a[i].first == 1){
			cout << i << endl;
			return;
		}
	}
	cout << n << endl;
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
