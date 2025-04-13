#define testcases
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define int long long
#define printmsg(msg, first, last) cerr << msg; for (auto it = first; it != last; it++) cerr << *it << " "; cerr << endl

const i64 INF = (i64)(2e9);

void solve(){
    i64 n;
    cin >> n;
    i64 a[2][n];
    for (i64 i = 0; i < 2; i++){
        for (i64 j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    // only RIGHT or DOWN
    // if down at i then you take a[0][i] + a[1][i]
    //  = max(a[0][i], a[1][i]) + min(a[0][i], a[1][i])
    // and for any j != i you can take max(a[0][j], a[1][j])
    // by positioning column j before or after i
    i64 s = 0;
    for (i64 i = 0; i < n; i++) s += max(a[0][i], a[1][i]);
    i64 ans = -INF;
    for (i64 i = 0; i < n; i++){
        i64 x = s + min(a[0][i], a[1][i]);
        ans = max(ans, x);
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
