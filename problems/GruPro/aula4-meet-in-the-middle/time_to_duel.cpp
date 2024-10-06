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
	i64 n, a, d, h;
	cin >> n >> a >> d >> h;
	i64 x[n], y[n], z[n];
	for (i64 i = 0; i < n; i++){
		cin >> x[i] >> y[i] >> z[i];
	}

	bool ok = false;
	for (i64 mask = 0; mask < (1ll << n); mask++){
		i64 aa = 0, dd = 0, hh = 0;
		for (i64 i = 0; i < n; i++){
			if (mask & (1ll << i)){
				aa += x[i];
				dd += y[i];
				hh += z[i];
			}
		}
		ok = ok || ((aa == a) && (dd == d) && (hh == h) && (__builtin_popcount(mask) > 1));
	}
	if (ok){
		cout << "Y" << endl;
	} else {
		cout << "N" << endl;
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
