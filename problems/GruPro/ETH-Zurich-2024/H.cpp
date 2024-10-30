#define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t
#define endl '\n'

bool check(i64 k, vector<vector<i64>>& v, const i64 n){
    const i64 m = v.size();
    if (k * m > n){
        return false; // just to avoid allocating memmory for huge values like n * m
    }
    vector<i64> times(k * m);
    i64 r = k * m - 1;
    for (i64 i = 0; i < m; i++){
        if (k > v[i].size()) return false;
        for (i64 j = (i64)v[i].size() - 1; j >= (i64)v[i].size() - k; j--){
            times[r] = v[i][j];
            --r;
        }
    }
    sort(times.begin(), times.end());

    bool ok = true;
    for (i64 i = 0; i < k * m; i++){
        ok = ok & (times[i] >= i);
    }
    return ok;
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    i64 a[n], b[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        --a[i];
    }
    for (i64 i = 0; i < n; i++){
        cin >> b[i];
    }

    vector<vector<i64>> v(m);
    for (i64 i = 0; i < n; i++){
        v[a[i]].emplace_back(b[i]);
    }
    for (i64 i = 0; i < m; i++){
        sort(v[i].begin(), v[i].end());
    }

    i64 l = 0, r = n, ans = 0;
    while (l <= r){
        const i64 mid = l + (r - l) / 2;
        if (check(mid, v, n)){
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
}

signed main(){
    i64 t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    for (i64 _ = 0; _ < t; _++){
        solve();
    }
}