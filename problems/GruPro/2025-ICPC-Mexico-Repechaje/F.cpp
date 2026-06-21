#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define i64 int64_t

signed main(){
    fastio;
    map<i64, i64> expected, actual;
    i64 x;
    for (i64 i = 0; i < 5; i++){
        cin >> x;
        ++expected[x]; 
    }
    for (i64 i = 0; i < 4; i++){
        cin >> x;
        ++actual[x];
    }
    for (const auto&[n, cnt]: expected){
        if (actual[n] < cnt){
            cout << n << endl;
            return 0;
        }
    }
}