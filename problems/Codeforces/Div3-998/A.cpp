#define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define i64 int64_t
#define endl "\n"

i64 score(i64 a[5]){
    i64 s = 0;
    for (i64 i = 0; i + 2 < 5; i++){
        s += (a[i + 2] == (a[i + 1] + a[i]));
    }
    return s;
}

void solve(){
    i64 a[5];
    cin >> a[0] >> a[1] >> a[3] >> a[4];

    // IF: a[2] = a[0] + a[1]
    // then a[3] = a[2] + a[1] = a[0] + 2a[1]
    // and a[4] = a[3] + a[2] = 2a[0] + 3a[1]

    i64 max_score = 0;
    a[2] = a[0] + a[1];
    max_score = max(max_score, score(a));
    a[2] = a[3] - a[1];
    max_score = max(max_score, score(a));
    a[2] = a[4] - a[3];
    max_score = max(max_score, score(a));
    cout << max_score << endl;
}

signed main(){
    fastio;
    int t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--) solve();
}