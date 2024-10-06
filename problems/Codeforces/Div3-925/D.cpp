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
	i64 n, x, y;
	cin >> n >> x >> y;

	map<pair<i64, i64>, i64> cnt;
	i64 a[n];
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
		++cnt[make_pair(a[i] % x, a[i] % y)];
	}

	i64 tot = 0;
	for (auto it = cnt.begin(); it != cnt.end(); it++){
		i64 rx = (it->first).first, ry = (it->first).second;
		if (rx != ((x - rx) % x)){
			tot += (it->second) * cnt[make_pair((x - rx) % x, ry)];
		} else {
			tot += (it->second) * (cnt[make_pair((x - rx) % x, ry)] - 1);
		}
	}
	tot /= 2;
	cout << tot << endl;
}
 
signed main(){
	fastio;
	// freopen("/tmp/in", "r", stdin);
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
