#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

void solve(){
    i64 n;
    cin >> n;
    set<i64> s;
    vector<tuple<i64, i64, string>> v;
    v.resize(n);
    for (i64 i = 0; i < n; i++){
        string c;
        i64 p, e[6];
        cin >> c >> p;
        for (i64 j = 0; j < 6; j++){
            cin >> e[j];
        }
        sort(e, e + 6);
        v[i] = tuple<i64, i64, string>((i64)10 * p + e[1] + e[2] + e[3] + e[4], -i, c);
        s.insert(-get<0>(v[i]));
    }

    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    i64 last = -1;
    i64 score = get<0>(v[0]);
    cout << get<2>(v[0]) << " " << get<0>(v[0]) << endl;
    for (i64 i = 1; i < min((int)v.size(), 1000); i++){
        // if it changed, then the last should be i - 1
        if (get<0>(v[i]) != score){
            score = get<0>(v[i]);
            last = i - 1;
        }
        if (last + 1 <= 2){
            cout << get<2>(v[i]) << " " << get<0>(v[i]) << endl;
        } else {
            break;
        }
    }
}

signed main(){
    fastio;
    solve();
}