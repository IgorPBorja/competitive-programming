#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

void solve(){
    i64 m, n;
    cin >> m >> n;
    i64 a[m], b[n];
    i64 ea = m, eb = n;
    for (i64 i = 0; i < m; i++){
        cin >> a[i];
        ea += a[i];
    }
    for (i64 j = 0; j < n; j++){
        cin >> b[j];
        eb += b[j];
    }
    if (ea > eb){
        cout << "ALICE" << endl;
    } else if (eb > ea) {
        cout << "BOB" << endl;
    } else {
        cout << "TIED" << endl;
    }
}

signed main(){
    fastio;
    solve();
}
