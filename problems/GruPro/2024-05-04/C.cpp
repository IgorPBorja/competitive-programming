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
	map<i64, i64> prime_cnt;	
	i64 n;
	cin >> n;
	i64 orig_n = n;

	// cerr << "TESTCASE=" << n << endl;
	for (i64 p = 2; p * p <= orig_n; p++){
		// cerr << "testing p=" << p << endl;
		// cerr << "stop=" << !(p * p <= orig_n) << endl;
		while (n % p == 0){
			++prime_cnt[p];
			n /= p;
			// cerr << "n=" << n << " p=" << p << endl;
		}
	}
	if (n > 1){
		// prime div remains
		++prime_cnt[n];
	}

	if (prime_cnt.size() == 1){
		// prime power p^x ==> if p <= 5 impossible, else take p^1, p^2, p^3
		i64 p = prime_cnt.begin()->first;
		i64 e = prime_cnt.begin()->second;
		if (e < 6){
			cout << "NO" << endl;
		} else {
			cout << "YES" << endl;
			cout << p << " " << p * p << " " << orig_n / (p * p * p) << endl;
		}
	} else if (prime_cnt.size() == 2){
		auto it = prime_cnt.begin();
		i64 p1 = it->first, e1 = it->second;
		++it;
		i64 p2 = it->first, e2 = it->second;
		if (e1 * e2 <= 2){
			cout << "NO" << endl;
		} else {
			cout << "YES" << endl;
			cout << p1 << " " << p2 << " " << orig_n / (p1 * p2) << endl;
		}
	} else {
		auto it = prime_cnt.begin();
		i64 p1 = it->first;
		++it;
		i64 p2 = it->first;
		cout << "YES" << endl;
		cout << p1 << " " << p2 << " " << orig_n / (p1 * p2) << endl;
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
