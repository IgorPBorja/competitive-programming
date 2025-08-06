/**
  after
  0 1 5 9 15 21 25 29 35

  the delta follow the cyclic pattern 4 12 4 4 10
  **/
#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t

int main(){
	i64 MAXN;
	cin >> MAXN;
    assert(MAXN >= 35);  // else breaks

    // BRUTE FORCE APPROACH (commented out, is quadratic)
	// i64 dp[MAXN + 1];
	// vector<i64> cnt(2 * MAXN + 1, 0);
	// 
	// i64 losing = 0;
	// for (i64 n = 0; n <= MAXN; n++){
	// 	vector<i64> v;
	// 	for (i64 i = 0; i + 1 < n; i++){
	// 		i64 g = dp[i] ^ dp[n - i - 2]; 
	// 		if (g <= 2 * MAXN) ++cnt[g];
	// 	}
	// 	i64 mex = 0;
	// 	for (; mex <= 2 * MAXN; mex++){
	// 		if (cnt[mex] == 0) break;
	// 	}
	// 	for (i64 i = 0; i + 1 < n; i++){
	// 		i64 g = dp[i] ^ dp[n - i - 2]; 
	// 		if (g <= 2 * MAXN) --cnt[g];
	// 	}
	// 	dp[n] = mex;
	// 	losing += (dp[n] == 0);
	// }
	// cout << "real losing=" << losing << endl;

	i64 losing = 9;
	i64 deltas[] = {4, 12, 4, 4, 10};
	i64 idx = 0;
	i64 cur = 35;
	while (cur + deltas[idx] <= MAXN){
		++losing;  // cur + deltas[idx]
		cur += deltas[idx];
		idx = (idx + 1) % 5;
	}
	cout << "estimated losing=" << losing << endl;
    // -1 since n=0 does not count
	cout << "estimated winning (final answer)=" << MAXN - (losing - 1) << endl;
}
