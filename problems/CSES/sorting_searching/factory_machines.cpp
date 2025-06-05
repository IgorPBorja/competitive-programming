#include <bits/stdc++.h>
using namespace std;
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define i64 int64_t
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;


template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> p){
    os << "(" << p.first << "," << p.second << ")";
    return os;
}


int main()
{
    fastio;

    i64 n, t;
    cin >> n >> t;
    i64 a[n];
    for (i64 i = 0; i < n; i++) cin >> a[i];

    // t = 1e9, n = 1, a[0] = 1e9 is worst case ==> ans = 1e18
    i64 l = 1, r = (i64)1e18, ans = r;
    while (l <= r){
        const i64 m = l + (r - l) / 2;
        i64 s = 0;
        for (i64 i = 0; i < n; i++) s = min((i64)1e18, s + m / a[i]);  // prevent overflow in long long
        // m / a[i] <= 1e18 / 1 ==> s + m/a[i] <= 2e18
        if (s >= t){
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << ans << endl;
}
