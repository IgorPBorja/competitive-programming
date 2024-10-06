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

vector<i64> subseq_sums(vector<i64> a, i64 mod){
	const i64 n = a.size();
	set<i64> s;
	// cout << "a="; print(a);
	for (i64 mask = 0; mask < (1ll << n); mask++){
		i64 sum = 0;
		for (i64 j = 0; j < n; j++){
			sum = (sum + ((mask >> j) & 1) * a[j]) % mod;
		}
		// printf("mask = %li, sum = %li\n", mask, sum);
		s.insert(sum);
	}
	vector<i64> ans;
	for (i64 x: s) ans.emplace_back(x);
	return ans;
}

void solve(){
	i64 n, m;
	cin >> n >> m;

	vector<i64> a(n / 2), b(n - n / 2);
	for (i64 i = 0; i < n / 2; i++){
		cin >> a[i];
	}
	for (i64 i = n / 2; i < n; i++){
		cin >> b[i - n / 2];
	}

	vector<i64> lsum = subseq_sums(a, m), rsum = subseq_sums(b, m);

	// print(lsum);
	// print(rsum);

	// two-pointers
	i64 max_m = 0;
	i64 r = 0;  // guaranteed rsum[0] == 0
	for (i64 l = lsum.size() - 1; l >= 0; l--){
		while (r + 1 < rsum.size() && lsum[l] + rsum[r + 1] < m){
			++r;			
		}
		max_m = max(lsum[l] + rsum[r], max_m);
	}
	cout << max_m << endl;
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
