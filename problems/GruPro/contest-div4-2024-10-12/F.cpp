// #define TESTCASES

#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'

#define int long long
using namespace std;

void solve(){
    int n, k;
    cin >> n >> k;
    --k;

    vector<int> a, b;
    a.reserve(10000);
    b.reserve(10000);
    for (int i = 1; i * i <= n; i++){
        if (n % i == 0){
            a.emplace_back(i);
            if (i < n / i){
                b.emplace_back(n / i);
            }
        }
    }
    reverse(b.begin(), b.end());
    if (k < a.size()){
        cout << a[k] << endl;
    } else if (k < a.size() + b.size()){
        cout << b[k - a.size()] << endl;
    } else {
        cout << -1 << endl;
    }
}

signed main(){
    fastio;
    int t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--){
        solve();
    }
}

