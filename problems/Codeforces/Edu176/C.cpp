#define testcases
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define int long long
#define printmsg(msg, first, last) cerr << msg; for (auto it = first; it != last; it++) cerr << *it << " "; cerr << endl

void solve(){
    i64 n, m;
    cin >> n >> m;
    i64 a[m];
    for (i64 i = 0; i < m; i++) cin >> a[i];

    // for each x we need how many options a[j] >= x
    // increments p[a[j]] for each j and do suffix sum
    vector<i64> suf(n + 1, 0);
    for (i64 i = 0; i < m; i++){
        ++suf[a[i]];
    }
    for (i64 i = n - 1; i >= 0; i--){
        suf[i] += suf[i + 1];
    }
    // for each paint i and for each choice j <= a[i]
    // we can choose suf[n - j] options
    i64 ans = 0;
    // using x|n-x dist
    // #{a[i] >= x} * #{a[i] >= n-x} - #{a[i] >= x && a[i] >= n-x}
    // can't have n|0 according to the problem, nor 0|n
    for (i64 x = 1; x < n; x++){
        i64 delta = suf[x] * suf[n - x] - suf[max(x, n - x)];
        ans += delta;
    }
    cout << ans << endl;
}

signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}

