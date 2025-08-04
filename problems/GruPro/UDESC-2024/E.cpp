#include<bits/stdc++.h>

using namespace std;
#define i64 long long
#define all(a) a.begin(),a.end();

void solve(){
    i64 n, q;
    cin >> n >> q;
    vector<i64> gcds(n);

    vector<i64> inits(n);
    for (i64 i = 0; i < n; i++){
        cin >> inits[i];
    }
    gcds[0] = inits[0];
    for (i64 i = 1; i < n; i++){
        gcds[i] = __gcd(gcds[i - 1], inits[i]);
    }
    
    for (i64 i = 0; i < q; i++){
        i64 mode;
        cin >> mode;
        if (mode == 1){
            // new
            i64 g;
            cin >> g;
            gcds.emplace_back(__gcd(gcds.back(), g));
        } else if (mode == 2){
            // discard
            i64 k;
            cin >> k;
            for (i64 _ = 0; _ < k; _++){
                gcds.pop_back();
            }
        } else {
            // print
            i64 x;
            cin >> x;
            cout << (gcds.back() % x == 0 ? "SIM" : "NAO") << endl;
        }
    }
}

signed main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(t--)solve();
}
