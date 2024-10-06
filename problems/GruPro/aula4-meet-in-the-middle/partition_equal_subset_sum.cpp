// NOTE: link: https://leetcode.com/problems/partition-equal-subset-sum/description/ 

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


bool canPartition(vector<int>& nums) {
	const int64_t numElems = nums.size();
	const int64_t total_sum = accumulate(nums.begin(), nums.end(), 0);
	if (total_sum % 2 == 1){
	    return false;
	}

	set<int64_t> possible_sum;
	possible_sum.insert(0);

	for (int64_t pivot = 0; pivot < numElems; pivot++){
	    // pivot is the last element in the first set
	    // update all possible sums by adding (or not adding) pivot
	    for (int64_t s: possible_sum){
		possible_sum.insert(s + nums[pivot]);
		cerr << "s=" << s << "->s+pivot=" << s + nums[pivot] << endl;
	    }
	    if (possible_sum.find(total_sum / 2) != possible_sum.end()){
		return true;
	    }
	}
	return false;
}

void solve(){
	int64_t n;
	cin >> n;
	vector<int> a(n);
	for (int64_t i = 0; i < n; i++){
		cin >> a[i];
	}
	cerr << "INPUT OK!" << endl;
	cout << canPartition(a) << endl;
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
