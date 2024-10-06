//#define TESTCASES

#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define i64 int64_t
#define endl '\n'

#define ep emplace
#define eb emplace_back

/*
* cases for dp[i]
* 1. the best solution (in terms of cnt, and then by final health)
*	is not enough, and dp[i - 1] + a[i] < 0
*	1.1 if some element x is < a[i], then swap x by a[i] and improve final health. To get the best improvement always, pick the smallest x
*	1.2 a[i] is less than the worst potion ==> just ignore it
* 2. can grab the a[i]: do it
*
*/

void solve(){
	i64 n;
	cin >> n;
	vector<i64> a(n);
    	for (i64 i = 0; i < n; i++) cin >> a[i];
	
	priority_queue<i64, vector<i64>, greater<i64>> potions_drank;
	i64 cur = 0;
	i64 cnt = 0;
	for (i64 i = 0; i < n; i++){
		if (a[i] >= 0){
			// always grab
			// do not need to go into pq (for optimization purposes)
			++cnt;
			cur += a[i];
		} else {
			// can grab without dying: do it! We will improve our margin later
			if (cur + a[i] >= 0){
				potions_drank.push(a[i]);
				++cnt;
				cur += a[i];
			} else if (potions_drank.size() > 0 && a[i] >= potions_drank.top()){
				i64 x = potions_drank.top();
				potions_drank.pop();
				potions_drank.push(a[i]);
				cur += a[i] - x;
			}
		}
	}
	cout << cnt << endl;
}

signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--) solve();
}
