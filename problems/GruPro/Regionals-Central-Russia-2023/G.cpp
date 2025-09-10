#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define printmsg(msg, first, last) cout << msg;for(auto it=first;it!=last;it++)cout<<*it<<" ";cout<<endl

const i64 MOD = (i64)1e9 + 7;

int main(){
    i64 n, k[3];
    cin >> n >> k[0] >> k[1] >> k[2];

    i64 dp[3][n + 1];
    i64 epref_dp[3][n + 2];
    for (i64 c = 0; c < 3; c++){
        dp[c][1] = 1;
        epref_dp[c][1] = 0;
        epref_dp[c][2] = 1;
    }
    for (i64 i = 2; i <= n; i++){
        for (i64 c = 0; c < 3; c++){
            i64 x = (epref_dp[(c + 1) % 3][i] + MOD - epref_dp[(c + 1) % 3][max((i64)1, i - k[c])]) % MOD;
            i64 y = (epref_dp[(c + 2) % 3][i] + MOD - epref_dp[(c + 2) % 3][max((i64)1, i - k[c])]) % MOD;
            i64 solo = (i <= k[c]) ? 1 : 0;
            dp[c][i] = (x + y + solo) % MOD;
            epref_dp[c][i + 1] = (epref_dp[c][i] + dp[c][i]) % MOD;
        }
    }
    // for (i64 c = 0; c < 3; c++){
    //     printmsg("c=" << c << " dp=", dp[c], dp[c] + n + 1);
    //     printmsg("c=" << c << " dp=", dp[c], dp[c] + n + 1);
    // }
    cout << (dp[0][n] + dp[1][n] + dp[2][n]) % MOD << endl;
}