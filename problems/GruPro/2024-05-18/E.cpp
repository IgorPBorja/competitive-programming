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

i64 bexp(i64 a, i64 p){
	if (p == 0){
		return 1;
	} else {
		i64 m = bexp(a, p / 2);
		return (i64)(p % 2) * (m * m * a) + (i64)(1 - (p % 2)) * (m * m);
	}
}

// moves = mismatches + what remains of the base
i64 moves(vector<i64> v, vector<i64> base){
	i64 b_ptr = 0;
	i64 mismatches = 0;
	for (i64 i = 0; i < v.size(); i++){
		if (b_ptr < base.size() && v[i] == base[b_ptr]){
			++b_ptr;
		} else {
			++mismatches;
		}
	}
	return mismatches + ((i64)base.size() - b_ptr);
}

vector<i64> to_vec(i64 n, i64 b=10){
	vector<i64> ans;
	while (n > 0){
		ans.emplace_back(n % b);
		n /= b;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

// invariant: number stays with the same size
// we need the power of two with the same size that has the
// maximum prefix which is a subsequence of the original number
void solve(){
	i64 n;
	cin >> n;

	if (n == (i64)1e9){
		cout << 9 << endl;
		return;
	}

	// at most we will use 2 * v.size() digits since this will take at the minimum
	// v.size() operations (if just adding for ex.)
	// and there is a solution in v.size() + 1 operations: remove everything and put 1
	// with the exception of n = 1e9, size of n is <= 9 ==> at most 18 operations (or 10^18)
	vector<i64> v = to_vec(n);
	i64 hi = bexp(10, 2 * v.size());  // 2 * v.size() digits wide

	i64 cur = 1;
	i64 ans = 2e18;
	while (cur < hi){
		ans = min(ans, moves(v, to_vec(cur)));
		cur *= (i64)2;
	}

	cout << ans << endl;
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
