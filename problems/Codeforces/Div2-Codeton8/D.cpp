#define TESTCASES
 
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

const i64 INF = 2e18;

bool add(multiset<i64>& topk, i64 x, i64 k){
	multiset<i64>::iterator start = topk.begin();
	if (topk.size() >= k && x <= *start){
		return false;
	}
	if (topk.size() >= k && x > *start){
		topk.erase(start);
		topk.insert(x);
		return true;
	} else {
		topk.insert(x);
		return true;
	}
}

void solve(){
	i64 n, k;
	cin >> n >> k;
	vector<vector<i64>> a(n, vector<i64>(n));
	for (i64 i = 0; i < n; i++){
		for (i64 j = i; j < n; j++){
			cin >> a[i][j];
		}
	}
	// vector<multimultiset<i64, greater<i64>>> dp(n);  // O(nk)
	vector<multiset<i64>> dp(n);
	add(dp[0], 0, k);
	add(dp[0], a[0][0], k);
	
	// calculate forwards
	for (i64 r = 1; r < n; r++){
		dp[r] = dp[r - 1];
		add(dp[r], a[0][r], k);
		add(dp[r], a[1][r], k);
		for (i64 l = 2; l <= r; l++){
			for (multiset<i64>::reverse_iterator it = dp[l - 2].rbegin(); it != dp[l - 2].rend(); it++){
				i64 x = *it;
				if (!add(dp[r], x + a[l][r], k)) break;
			}
		}
	}

	for (multiset<i64>::reverse_iterator it = dp[n - 1].rbegin(); it != dp[n - 1].rend(); ++it){
		cout << *it << " ";
	}
	cout << endl;
}
 
signed main(){
	fastio;
	int t;
	// freopen("/tmp/in", "r", stdin);
#ifdef TESTCASES
	cin >> t;
#else
	t = 1;
#endif
	while (t--){
		solve();
	}
}
