#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

signed main(){
    i64 n;
    cin >> n;
    pair<i64, i64> a[n];
    i64 s[2] = {0, 0};
    map<pair<i64, i64>, i64> cnt;
    for (i64 i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
        ++cnt[a[i]];
        s[0] += a[i].first;
        s[1] += a[i].second;
    }

    if (n % 2 == 1){
        cout << "impossible" << endl;
        return 0;
    }
    if ((s[0] % (n / 2) != 0) || (s[1] % (n / 2) != 0)){
        cout << "impossible" << endl;
        return 0;
    }
    i64 m[2] = {s[0] / (n / 2), s[1] / (n / 2)};
    for (auto[k, v]: cnt){
        auto k2 = make_pair(m[0] - k.first, m[1] - k.second);
        if (cnt.find(k2) == cnt.end()){
            cout << "impossible" << endl;
            return 0;
        }
        if (k2 == k){
            // just need v to be even
            if (v % 2 == 1){
                cout << "impossible" << endl;
                return 0;
            }
        }
        --cnt[k2];
        --cnt[k];
    }
    cout << "possible" << endl;
}