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
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 MAXN = 2e4 + 5;
const i64 INF = 1e18;

void solve(){
	i64 n, m;
	cin >> n >> m;

	i64 dp[MAXN + 1];
	for (i64 i = 0; i < MAXN + 1; i++) dp[i] = INF;
	dp[n] = 0;
	
	// do a single pass to try and update all numbers (at most MAXN)
	while (true){
		bool improved = false;
		i64 mirror[MAXN + 1];
		for (i64 j = 0; j <= MAXN; j++){
			if (j % 2 == 0){
				if (1 + min(dp[j / 2], dp[j + 1]) < dp[j]){
					mirror[j] = 1 + min(dp[j / 2], dp[j + 1]);
					// cout << "improved in j=" << j << endl;
					improved = true;
				} else {
					mirror[j] = dp[j];
				}
			} else {
				if (1 + dp[j + 1] < dp[j]){
					mirror[j] = 1 + dp[j + 1];
					// cout << "improved in j=" << j << endl;
					improved = true;
				} else {
					mirror[j] = dp[j];
				}
			}
		}
		if (!improved) break;
		for (i64 j = 0; j <= MAXN; j++){
			dp[j] = mirror[j];
		}
	}
	cout << dp[m] << endl;
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
