#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

const i64 MOD = (i64)1e9 + 7;

i64 bexp(i64 a, i64 p) {
    if (p == 0) return 1;
    else {
        const i64 b = bexp(a, p / 2);
        const i64 b2 = (b * b) % MOD;
        if (p % 2) return (a * b2) % MOD;
        else return b2;
    }
}

i64 inv(i64 a) { return bexp(a, MOD - 2); }

signed main(){
    i64 a, b, n;
    cin >> a >> b >> n;

    // Maximum sum for integers of length n is d = 9 * n
    // For every good number y <= d
    // Length of y is log(n) ==> 2^log(n) ~ O(n) options
    // We want all good numbers x of length n with digit_sum(x) = y

    // say x has n-k times a and k times b
    // then (n-k)*a + k*b = y ==> k(b-a) = y-na
    // so there is only one possible k, IF b-a divides y-na and y-na >= 0
    // and for every k there are choose(n, k) permutations
    // O(1) check per O(n) option

    vector<i64> fat(n + 1), ifat(n + 1);
    fat[0] = 1;
    for (i64 i = 1; i <= n; i++) fat[i] = (fat[i - 1] * i) % MOD;
    ifat[n] = inv(fat[n]);
    for (i64 i = n - 1; i >= 0; i--) ifat[i] = (ifat[i + 1] * (i + 1)) % MOD;

    auto choose = [&fat, &ifat](i64 n, i64 k){
        return (((fat[n] * ifat[k]) % MOD) * ifat[n - k]) % MOD;
    };

    i64 ans = 0;
    // 9 * n <= 9 * MAXN = 9e6 < 1e7, 7 choices
    for (i64 len_digit_sum = 1; len_digit_sum <= 7; len_digit_sum++){
        for (i64 msk = 0; msk < (1ll << len_digit_sum); msk++){
            i64 y = 0;
            i64 p10 = 1;
            for (i64 i = 0; i < len_digit_sum; i++, p10 *= 10){
                if (msk & (1ll << i)) y += b * p10;
                else y += a * p10;
            }
            if (y > 9 * n) break;  // y is increasing as msk increases because of encoding
            // if y > 9 * n, it is impossible

            // sum of digits is y
            if (y - n * a >= 0 && (y - n * a) % (b - a) == 0){
                i64 k = (y - n * a) / (b - a);
                if (0 <= k && k <= n) {
                    ans = (ans + choose(n, k)) % MOD;
                    // cout << "y=" << y << " n-k=" << n-k << " copies of a=" << a
                    //     << " and k=" << k << " copies of b=" << b << endl;
                }
            }
        }
    }
    cout << ans << endl;
}