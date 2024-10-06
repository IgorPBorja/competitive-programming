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

vector<i64> lset, rset;
vector<i64> a;

// void sum_subsets(map<i64, i64> &ans, i64 r, i64 i, i64 cur=0){
// 	if (i == r){
// 		++ans[cur];
// 	} else {
// 		sum_subsets(ans, r, i + 1, cur);
// 		sum_subsets(ans, r, i + 1, cur + a[i]);
// 	}
// }

// interval [l, r) (exclusive on right endpoint)
void sum_subsets(vector<i64> &ans, i64 l, i64 r){
	for (i64 mask = 0; mask < (1 << (r - l)); mask++){
		i64 sum = 0;
		for (i64 i = 0; i < r - l; i++){
			if (mask & (1 << i)){
				sum += a[l + i];
			}
		}
		ans.emplace_back(sum);
	}
}

void solve(){
	i64 n, x;	
	cin >> n >> x;
	a.resize(n);
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	lset.reserve(1 << 20);
	rset.reserve(1 << 20);

	sum_subsets(lset, 0, n / 2); // <= 1<<20
	sum_subsets(rset, n / 2, n); // <= 1<<20
	sort(lset.begin(), lset.end());
	sort(rset.begin(), rset.end());

	// print(lset);
	// print(rset);

	i64 total = 0;
	for (i64 y: lset){
		auto lo = lower_bound(rset.begin(), rset.end(), x - y);
		auto hi = upper_bound(rset.begin(), rset.end(), x - y);
		total += hi - lo;
	}
	cout << total << endl;
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
