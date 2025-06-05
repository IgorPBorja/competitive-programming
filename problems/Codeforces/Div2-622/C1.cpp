// #define testcases
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define int long long
#define i64 int64_t
#define printmsg(msg, first, last) cout << msg; for (auto it = first; it != last; it++) cout << *it << " "; cout << endl


template <typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> p){
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

const i64 INF = (i64)2e18;

i64 argmin(i64 a[], i64 l, i64 r){
    i64 m = a[l], pos = l;
    for (i64 i = l + 1; i <= r; i++){
        if (a[i] < m){
            m = a[i];
            pos = i;
        }
    }
    return pos;
}

pair<i64, vector<i64>> f(i64 a[], i64 l, i64 r){
    if (l > r){
        return {0, {}};
    }
    i64 i = argmin(a, l, r);
    for (i64 j = l; j < i; j++) a[j] -= a[i];
    auto[sl, bl] = f(a, l, i - 1);
    // global over sl gains a[i] * (r - l + 1), a[i] on everyone 
    
    for (i64 j = i + 1; j <= r; j++) a[j] -= a[i];
    auto[sr, br] = f(a, i + 1, r);
    // global over sr gains a[i] * (r - l + 1), a[i] on everyone
    
    vector<i64> b;
    if (sr > sl){
        for (i64 j = l; j <= i; j++) b.emplace_back(a[i]);
        for (i64 j = i + 1; j <= r; j++){
            b.emplace_back(br[j - i - 1] + a[i]);
        }
    } else {
        for (i64 j = l; j < i; j++) b.emplace_back(bl[j - l] + a[i]);
        for (i64 j = i; j <= r; j++) b.emplace_back(a[i]);
    }
    return {max(sl, sr) + a[i] * (r - l + 1), b};
}

void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++) cin >> a[i];
    
    auto[_, b] = f(a, 0, n - 1);
    for (i64 i = 0; i < n; i++) cout << b[i] << " ";
    cout << endl;
}

signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}
