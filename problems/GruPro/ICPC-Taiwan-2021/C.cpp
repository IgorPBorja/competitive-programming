// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

i64 count_inversions(i64 a[], i64 l, i64 r){
    if (l == r) return 0;
    else {
        const i64 m = l + (r - l) / 2;
        i64 x1 = count_inversions(a, l, m);
        i64 x2 = count_inversions(a, m + 1, r);
        // we assume now halves are sorted
        // now sort
        vector<i64> b(r - l + 1);
        i64 p1 = l, p2 = m + 1, pg = 0;
        i64 ans = x1 + x2;
        i64 local = 0;
        // we only count the cross-inversion (a[x], a[y])
        // with a[x] > a[y] and l <= x <= m and m + 1 <= y <= r
        // from the y perspective, which explains the position of the `local` increment
        // (NO double counting)
        while (p1 <= m || p2 <= r){
            if (p2 > r){
                b[pg++] = a[p1++];
            } else if (p1 > m){
                b[pg++] = a[p2++];
            } else {
                if (a[p1] < a[p2]){
                    b[pg++] = a[p1++];
                } else {
                    b[pg++] = a[p2++];
                    // inversion: this element in right half is smaller than
                    // a[p1...m]
                    local += m - p1 + 1;
                }
            }
        }
        copy(b.begin(), b.end(), a + l);
        // cout << "on l=" << l << " r=" << r << " we found inv=" << ans + local << " inversions" << endl;
        return ans + local;
    }
}

void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    cout << count_inversions(a, 0, n - 1) << endl;
}

signed main(){
    i64 t = 1;    
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--){
        solve();
    }
}