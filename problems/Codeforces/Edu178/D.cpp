#define testcases
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define int long long
#define printmsg(msg, first, last) cout << msg; for (auto it = first; it != last; it++) cout << *it << " "; cout << endl

const i64 INF = (i64)(2e9);

ostream& operator<<(ostream& os, tuple<i64, i64, i64, i64> t){
    os << "(" << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << " " << get<3>(t) << ")";
    return os;
}

// keep a set of positions and positions at empty tables
// if you take a position, remove it and remove the whole table from the empty table set.

vector<i64> sieve(i64 n){
    vector<i64> is_prime(n + 1, 1);
    vector<i64> primes;
    for (i64 i = 2; i <= n; i++){
        if (!is_prime[i]) continue;
        primes.emplace_back(i);
        for (i64 j = 2 * i; j <= n; j += i){
            is_prime[j] = false;
        }
    }
    return primes;
}

vector<i64> primes;
vector<i64> pref_primes;


void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    reverse(a, a + n);
    // greedy: keep larger so real >= target earlier
    
    i64 pref_a[n + 1];
    pref_a[0] = 0;
    for (i64 i = 0; i < n; i++){
        pref_a[i + 1] = pref_a[i] + a[i];
    }
    
    // printmsg("pref_a=", pref_a, pref_a + n + 1);
    // printmsg("pref_primes=", pref_primes.begin(), pref_primes.begin() + n + 1);
    
    // binary search on removal
    i64 l = 0, r = n, ans = n;
    while (l <= r){
        const i64 k = l + (r-l) / 2;
        i64 target = pref_primes[n - k];
        i64 real = pref_a[n - k];  // n-k larger
        if (real >= target){
            ans = k;
            r = k - 1;  // might remove less
        } else {
            l = k + 1;
        }
    }
    cout << ans << endl;
}

signed main(){
    primes = sieve((i64)1e7);
    pref_primes.resize(primes.size() + 1);
    pref_primes[0] = 0;
    for (i64 i = 0; i < primes.size(); i++){
        pref_primes[i + 1] = primes[i] + pref_primes[i];
    }
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}