#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t

signed main(){
    const i64 MAXM = 500000;
    vector<i64> cnt(MAXM + 1, 0);

    i64 n, x, a;
    cin >> n >> x;
    for (i64 i = 0; i < n; i++){
        cin >> a;
        ++cnt[a];
    }

    for (i64 i = 1; i < x; i++){
        cnt[i + 1] += cnt[i] / (i + 1);
        cnt[i] %= i + 1;
        if (cnt[i]){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}