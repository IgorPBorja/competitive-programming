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

// O(sqrt(N)) naive primality check
bool is_prime(i64 n){
	if (n == 0 || n == 1) return false;
	for (i64 i = 2; i * i <= n; i++){
		if (n % i == 0) return false;
	}
	return true;
}

void solve(){
	i64 n;
	cin >> n;

	i64 x = n / 2, y = (n + 1) / 2;
	while (x > 0 && (is_prime(x) || is_prime(y))){
		--x;
		++y;
	}
	if (x == 0){
		cout << -1 << endl;
	} else {
		// guaranteed at most three iterations for n large (say > 6 approx.)
		// since if n is 3 mod 4 (thus x is odd)
		// we can't have x, x + 2 and x - 2 being primes simultaneously (at least one is a multiple of 3)
		// analogous result for n = 1 mod 4
		cout << x << " " << y << endl;
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
