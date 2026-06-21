#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define i64 int64_t

/*
d = gcd(a[i], a[j])

go through the divisors of the first number

sieve everyone?

let c[p^k] how many integers are divisible by p^k
Then c[p^k] = n (if p^k | d) or c[p^k] = 1 because if 1 < c[p^k] < n then some pair has more p factors in common than other
and this is bad
*/

constexpr i64 MAXN = (i64)1e7 + 10;
vector<i64> primes;
constexpr i64 INF = (i64)2e18;
vector<i64> spf(MAXN + 1, INF);

void calc_spf(){
    for (i64 i = 2; i <= MAXN; i++){
        if (spf[i] != INF) continue;  // not prime
        spf[i] = i;
        primes.emplace_back(i);
        for (i64 j = 2 * i; j <= MAXN; j += i){
            spf[j] = min(spf[j], i);
        }
    }
}

signed main(){
    fastio;
    calc_spf();

    i64 n;
    cin >> n;
    vector<i64> a(n);
    vector<i64> cnt(MAXN + 1, 0);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        i64 cur = a[i];
        i64 p = spf[a[i]], x = p;
        while (cur > 1){
            // cerr << "at cur=" << cur << " p=" << p << endl;
            // get largest p^k | a[i]
            while (cur % p == 0){
                ++cnt[x];
                x *= p;
                cur /= p;
            }
            p = spf[cur];
            x = p;
        }
    }
    bool ok = true;
    for (i64 i = 2; i <= MAXN; i++){
        if (1 < cnt[i] && cnt[i] < n) ok = false;
    }
    cout << (ok ? "YES" : "NO") << endl;
}