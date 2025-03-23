#define TESTCASES
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
// no flush
#define endl '\n'

#define printmsg(msg, first, last) \
    cout << msg; \
    for (auto it = first; it != last; it++){ \
        cout << *it << " "; \
    } \
    cout << endl \

void solve(){
    i64 n, m;
    cin >> n >> m;
    cout << max(n, m) + 1 << endl;
}

signed main(){
    int t;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--){
        solve();
    }
}