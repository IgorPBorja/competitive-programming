// FIXME : does not work

#include <bits/stdc++.h>
using namespace std;
#define INF (int)(2e9)

int coinsum(int coins[], int m, int dp[], int target,
            int min_e){
    if (target == 0){
        return 0;
    } else if (target < min_e){
        return -1;
    } else if (dp[target] != -1){
        return dp[target];
    } else {
        for (int i = 0; i < m; i++){
            if (coins[i] <= target){
                int c = coins[i];
                int remaining = coinsum(coins, m, dp, target - c, min_e);
                if (remaining != -1){
                    // is possible 
                    dp[target] = dp[target] == -1 ? (remaining + 1) : 
                                                    (min(dp[target], remaining + 1));
                }
            } else {
                break;
            }
        }
        return dp[target];
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int m, target;
    cin >> m; 
    cin >> target;
    int coins[m];
    
    int min_e = INF;
    for (int i = 0; i < m; i++){
        cin >> coins[i];
        min_e = min(min_e, coins[i]);
    } 
    sort(coins, coins + m);

    int dp[target + 1];
    for (int i = 0; i < target + 1; i++) dp[i] = -1;

    cout << coinsum(coins, m, dp, target, min_e);
}
