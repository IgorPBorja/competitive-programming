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
	i64 n;
	string x;

	cin >> n >> x;
	i64 a[n], b[n];
	a[0] = 1; b[0] = 1;
	// the first will be chosen as the larget
	bool has_chosen = false;
	for (i64 i = 1; i < n; i++){
		if (x[i] == '0'){
			a[i] = 0;
			b[i] = 0;
		} else if (x[i] == '1'){
			if (!has_chosen){
				a[i] = 1;
				b[i] = 0;
				has_chosen = true;
			} else {
				a[i] = 0;
				b[i] = 1;
			}
		} else {
			if (!has_chosen){
				// not worth choosing 2 as would create a larger num than 1
				a[i] = 1;
				b[i] = 1;
			} else {
				// give the larger a 0 to stop its growth
				a[i] = 0;
				b[i] = 2;
			}
		}
	}
	for (i64 i = 0; i < n; i++){
		cout << a[i];
	}
	cout << endl;
	for (i64 i = 0; i < n; i++){
		cout << b[i];
	}
	cout << endl;
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
