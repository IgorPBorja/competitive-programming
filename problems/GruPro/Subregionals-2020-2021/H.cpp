#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define print(msg, v) cerr << msg; for (auto x: v) cerr << x << " "; cerr << endl

i64 choose[51][51];

// cnt numbers with k active bits in [0..x]
// complexity: O(B) = O(log x) because it is tail recursive
i64 cnt_prefix(i64 x, i64 k, i64 B){
    // cerr << "at x=" << x << " k=" << k << " B=" << B << endl;
    if (k == 0) return 1;  // 0
    else if (B == 0 && k == 1) return x & 1;  // 1
    else if (B == 0 && k > 1) return 0;  // too many

    if (x & (1ll << B)) {
        // don't take bit, or take bit
        i64 ans = choose[B][k] + cnt_prefix(x ^ (1ll << B), k - 1, B - 1);
        return ans;
    } else {
        i64 ans = cnt_prefix(x, k, B - 1);
        return ans;
    }
}


int main(){
    i64 n, k;
    cin >> n >> k;
    vector<i64> v(n);

    choose[0][0] = 1;
    for (i64 k = 1; k <= 50; k++) choose[0][k] = 0;
    for (i64 m = 1; m <= 50; m++){
        choose[m][0] = choose[m][m] = 1;
        for (i64 k = 1; k < m; k++){
            choose[m][k] = choose[m - 1][k - 1] + choose[m - 1][k];
        }
        for (i64 k = m + 1; k <= 50; k++) choose[m][k] = 0;
    }

    for (i64 i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());  // critical for lex ordering to work

    i64 a, b;
    cin >> a >> b;

    auto eval = [&v, n](i64 msk1){
        i64 s = 0;
        for (i64 i = 0; i < n; i++){
            if (msk1 & (1ll << i)) s += v[i];
        }
        return s;
    };

    i64 mask_lb = (1ll << n), mask_ub = 0;
    
    i64 l = 0, r = (1ll << n) - 1;

    while (l <= r){
        const i64 m = l + (r - l) / 2;
        if (eval(m) < a){
            l = m + 1;
        } else {
            mask_lb = m;
            r = m - 1;
        }
    }
    // cerr << "lb=" << mask_lb << endl;

    l = 0, r = (1ll << n) - 1;
    while (l <= r){
        const i64 m = l + (r - l) / 2;
        if (eval(m) > b){
            r = m - 1;
        } else {
            mask_ub = m;
            l = m + 1;
        }
    }
    // cerr << "ub=" << mask_ub << endl;

    if (mask_lb > mask_ub){
        cout << 0 << endl;
    } else {
        // cerr << "c35=" << cnt_prefix(mask_ub, k, n - 1) << endl;
        i64 ans = cnt_prefix(mask_ub, k, n - 1);
        // cerr << "c7=" << cnt_prefix(mask_lb, k, n - 1) << endl;
        if (mask_lb > 0) ans -= cnt_prefix(mask_lb - 1, k, n - 1);
        cout << ans << endl;
    }
}