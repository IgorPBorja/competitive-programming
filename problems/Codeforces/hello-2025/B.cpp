#define TESTCASES
#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

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
    i64 n, k;
    cin >> n >> k;
    map<i64, i64> cnt;
    i64 a[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        ++cnt[a[i]];
    }
    vector<i64> c;
    for (auto[k, v]: cnt){
        c.emplace_back(v);
    }
    sort(c.begin(), c.end());
    reverse(c.begin(), c.end());
    // map to largest class
    while (c.size() > 1 && k >= c.back()){
        k -= c.back();
        c[0] += c.back();
        c.pop_back();
    }
    cout << c.size() << endl;
}

signed main(){
    fastio;
    int t;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--){
        solve();
    }
}