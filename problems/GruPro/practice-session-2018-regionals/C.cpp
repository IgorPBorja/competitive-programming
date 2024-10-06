#include <bits/stdc++.h>
#define TESTCASES

using namespace std;

#define i64 int64_t

const i64 MOD = (i64)1e9 + 7;

i64 bexp(i64 a, i64 p){
    if (p == 0){
        return 1;
    } else {
        i64 m = bexp(a, p / 2);
        if (p % 2 == 0){
            return (m * m) % MOD;
        } else {
            return (((m * m) % MOD) * a) % MOD;
        }
    }
}

void solve(){
    i64 n;
    cin >> n;

    i64 ans = (n - 3) % MOD;
    ans = (ans * bexp(2, n)) % MOD;
    ans = (ans + n + 3) % MOD;
    cout << ans << endl;
}

signed main(){
    i64 t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    for (i64 i = 0; i < t; i++){
        solve();
    }
}