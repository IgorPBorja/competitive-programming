#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define print(msg, v) cerr << msg; for (auto x: v) cerr << x << " "; cerr << endl

vector<i64> sieve(const i64 MAXN){
    vector<i64> primes;  // about N/log N
    vector<i64> is_prime(MAXN + 1, true);
    for (i64 i = 2; i <= MAXN; i++){
        if (!is_prime[i]) continue;
        primes.emplace_back(i);
        for (i64 j = 2 * i; j <= MAXN; j += i){
            is_prime[j] = false;
        }
    }
    return primes;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    i64 m, n, k;
    cin >> m >> n >> k;

    vector<i64> primes = sieve((i64)3.5e7);
    // cerr << "sieve ok" << endl;
    vector<i64> c(n);
    for (i64 i = 0; i < n; i++) cin >> c[i];

    vector<vector<pair<i64, i64>>> adj(m);
    for (i64 i = 0; i < k; i++){
        i64 p_idx, n_idx, d;
        cin >> p_idx >> n_idx >> d;
        --p_idx; --n_idx;
        adj[p_idx].emplace_back(n_idx, d);
    }

    i64 p_idx = 0;
    vector<i64> ans(m);
    for (i64 p: primes){
        // cerr << "trying p=" << p << endl;
        if (p_idx >= m) break;
        bool ok = true;
        for (auto[i, _]: adj[p_idx]){
            if (c[i] % p != 0) {
                ok = false;
                break;
            }
        }
        if (ok){
            // cerr << "p=" << p << " is valid!" << endl;
            // cleanup
            for (auto[i, d]: adj[p_idx]){
                for (i64 j = 0; j < d; j++) c[i] /= p;
            }
            ans[p_idx++] = p;
            // print("c=", c);
        }
    }

    // prime is the remaining value
    for (; p_idx < m; p_idx++){
        i64 i = adj[p_idx][0].first;
        ans[p_idx] = c[i];
    }

    for (i64 i = 0; i < m; i++){
        cout << ans[i] << " ";
    }
    cout << endl;
}