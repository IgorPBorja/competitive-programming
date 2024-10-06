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
	i64 a, b, c;
	cin >> a >> b >> c;

	if (c != a + 1){
		cout << -1 << endl;
		return;
	} else if (a == 0){
		cout << b << endl;
		return;
	}

	// first h such that 2^h - 1 >= a
	// will be at least >= 1
	i64 h = 0;
	for (; (1ll << h) - 1 < a; h++); 

	// level h - 1 might be incomplete, try to complete it by hanging type-1 nodes (1 child)

	// now level h, if needed, will have 2 * (a - [(1ll << (h - 1)) - 1]) nodes (because the last had half the amount with 2 children)
	// + min(b, (1ll << h) - 1 - a) nodes  (children of type-1 nodes from last level)
	// and this amount will stay constant per level

	i64 k = 2 * (a - ((1ll << (h - 1)) - 1)) + min(b, ((i64)1 << h) - 1 - a);
	// cerr << "h=" << h << endl;
	// cerr << "k=" << k << endl;
	b -= (1ll << h) - 1 - a;
	// level h - 1 is now filled

	for (; b > 0; h++){ // still need a new level for b (need level h)
		b -= k;
	}
	cout << h << endl;
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
