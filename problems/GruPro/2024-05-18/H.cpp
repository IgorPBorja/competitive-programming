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

// 
/*
let k be sliding for each

the we store sum cnt[x, i + 1, k - 1] * cnt[x, k + 1, n - 1]
start with k = i + 1
when k slides, then cnt[a[k], i + 1, k' - 1] = cnt[a[k], i + 1, k - 1] + 1 and cnt[a[k + 1], k' + 1, n - 1] = cnt[a[k + 1], k + 1, n - 1] - 1
*/

const i64 M = 3000;

i64 answer_fixed_i(const vector<i64> &a, const i64 i){  // O(N + M)
	const i64 n = a.size();
	// middle: cnts all in range (i + 1, k - 1)
	// right: cnts all in range (k + 1, n - 1)
	// k starts at i + 1

	i64 middle[M + 1], right[M + 1];
	memset(middle, 0, sizeof middle);
	memset(right, 0, sizeof right);
	i64 sum = 0;
	for (i64 j = i + 2; j < a.size(); j++){
		++right[a[j]];
	}
	i64 ans = 0;
	for (i64 k = i + 2; k + 1 < n; k++){
		// if a[k - 1] = x and a[k] = y: (middle[x] + 1) * right[x] + (right[y] - 1) * middle[y]
		if (a[k] != a[k - 1]){
			sum += right[a[k - 1]] - middle[a[k]];
		}
		// if a[k - 1] = a[k] = x: (middle[x] + 1) * (right[x] - 1)
		else {
			sum += right[a[k - 1]] - middle[a[k]] - 1;
		}
		if (a[k] == a[i]){
			ans += sum;
		}
		// move division ptr to k
		// k-2 | k-1 | k ==> k-2 k-1 | k | k+1
		++middle[a[k - 1]];
		--right[a[k]];
	}
	return ans;
}

void solve(){
	i64 n;
	cin >> n;

	vector<i64> a(n);
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	i64 ans = 0;
	for (i64 i = 0; i + 4 <= n; i++){
		ans += answer_fixed_i(a, i);
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
