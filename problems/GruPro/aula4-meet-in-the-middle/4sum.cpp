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
	i64 n, target;
	cin >> n >> target;
	vector<i64> a(n);
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	i64 total = 0;
	map<i64, i64> count_sums_pairs;
	for (i64 pivot = 2; pivot < n; pivot++){
		// add all sums of pairs (pivot - 1, i)
		for (i64 i = 0; i < pivot - 1; i++){
			++count_sums_pairs[a[i] + a[pivot - 1]];
		}
		// try all l > pivot for the fourth value
		// the .find avoids creating unnecessary map keys
		for (i64 l = pivot + 1; l < n; l++){
			auto it = count_sums_pairs.find(target - a[l] - a[pivot]);
			if (it != count_sums_pairs.end()){
				total += it->second;
			}
		}
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
