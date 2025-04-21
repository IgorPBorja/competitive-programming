#define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define i64 int64_t
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++) cerr << *it << " "; cerr << endl
#define endl "\n"

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, pair<T, U> p){
    os << p.first << "," << p.second;
    return os;
}

void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++) cin >> a[i];

    for (i64 i = 0; i + 1 < n; i++){
        i64 m = min(a[i], a[i + 1]);
        a[i] -= m;
        a[i + 1] -= m;
    }

    // printmsg("a=", a, a + n);
    bool ok = true;
    for (i64 i = 0; i + 1 < n; i++) ok &= (a[i] <= a[i + 1]);
    cout << (ok ? "YES" : "NO") << endl;
}

signed main(){
    fastio;
    int t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--) solve();
}