#define testcases
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define int long long

void solve(){
    i64 n, k, x;
    cin >> n >> k >> x;
    i64 a[n];
    
    i64 total = 0;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        total += a[i];
    }
    
    i64 lptr = 0, rptr = -1, s = 0;
    i64 cnt = 0;
    // NOTE no subarray has sum 0
    
    for (; lptr < n; lptr++){
        if (lptr > 0) s -= a[lptr - 1];
        while (rptr + n < n * k && s + total < x){
            // MUST take a whole block
            rptr += n;
            s += total;
            // cout << "s=" << s << ", moved a block" << endl;
        }
        while (rptr + 1 < n * k && s < x){
            ++rptr;
            s += a[rptr % n];
            // cout << "s= " << s << ", moved one to rptr=" << (rptr % n) << endl;
        }
        // cout << "s=" << s << endl;
        // cout << "for l=" << lptr + 1 << " r=" << rptr + 1 << endl;
        if (s < x) break;
        // now for the **first** lptr we need that rptr
        // how many times can you sum n before rptr + c * n < n * k
        // <==> rptr + c * n <= n * k - 1 <==> 0 <= c <= k - (rptr + 1) / n
        // <==> 0 <= c <= k - ceil((rptr + 1) / n)
        i64 delta = 1 + k - ((rptr + 1) + n - 1) / n;
        cnt += delta;
    }
    cout << cnt << endl;
}

signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}

