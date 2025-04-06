#define testcases
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define int long long

#define printbin(msg, vec) cout << msg; for (auto bit: vec) cout << bit; cout << endl

const i64 B = 30;

void solve(){
    i64 x, y;
    cin >> x >> y;
    if (x == y) cout << -1 << endl;
    // raise closest to a power of 2
    // so we'd have (x,y) with x > y -> (2^(B+1), y') where y' is < 2^(B+1)
    // so it does not share any bits
    else cout << ((1ll << (B + 1)) - max(x, y)) << endl;
}

signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}
