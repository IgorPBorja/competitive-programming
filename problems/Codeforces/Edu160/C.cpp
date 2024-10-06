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

#define B 30

vector<i64> cnt(B, 0);

vector<i64> bin_repr(i64 x){
	vector<i64> bits(B, 0);
	i64 i = 0;
	while (x > 0){
		bits[B - 1 - i] = x % 2;
		x /= (i64)2;
		++i;
	}
	return bits;
}

bool _check(i64 i, vector<i64>& bits){
	// greedy approach
	if (i == B - 1){
		return cnt[i] >= bits[i];
	}
	// consume what you can
	bits[i] = max(bits[i] - cnt[i], (i64)0);
	// transfer bits
	bits[i + 1] += (i64)2 * bits[i];
	return _check(i + 1, bits);
}

bool check(i64 x){
	// get binary repr
	vector<i64> bits = bin_repr(x);
	return _check(0, bits);
}

void solve(){
	i64 m;
	cin >> m;

	i64 mode, x;
	for (i64 i = 0; i < m; i++){
		cin >> mode >> x;
		if (mode == 1){
			++cnt[B - 1 - x];
		} else {
			bool ok = check(x);
			if (ok){
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}
		}
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
