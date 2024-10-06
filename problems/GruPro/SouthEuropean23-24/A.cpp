#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define printmsg(msg, first, last) cout<<msg;for(auto it = first; it != last; it++)cout << *it << " ";cout << endl

void solve(){
    i64 n;
    cin >> n;
    pair<i64, i64> c[n];
    vector<i64> st[5];
    i64 pos[5][n];
    for (i64 i = 0; i < n; i++){
        char suit;
        i64 u, v;
        cin >> suit;
        cin >> v;
        --v;  // 0-indexed
        if (suit == 'S') {
            u = 0;
        } else if (suit == 'W') {
            u = 1;
        } else if (suit == 'E') {
            u = 2;
        } else if (suit == 'R') {
            u = 3;
        } else {
            u = 4;
        }
        c[i] = {u, v};
        st[u].emplace_back(v);
    }
    for (i64 i = 0; i < 5; i++){
        sort(st[i].begin(), st[i].end());
        // for (i64 j = 0; j < n; j++){
        //     pos[i][j] = -1;
        // }
        for (i64 j = 0; j < st[i].size(); j++){
            pos[i][st[i][j]] = j;
        }
    }
    // printmsg("st[0]", st[0].begin(), st[0].end());
    // printmsg("st[1]", st[1].begin(), st[1].end());
    // printmsg("st[2]", st[2].begin(), st[2].end());
    // printmsg("st[3]", st[3].begin(), st[3].end());
    // printmsg("st[4]", st[4].begin(), st[4].end());

    // internal position
    i64 p[5] = {0, 1, 2, 3, 4};
    i64 ans = 2e9;
    do {
        // position will be internal position + prefix sum
        // p[i] = position of i 
        i64 pref[6];
        pref[0] = 0;
        for (i64 i = 0; i < 5; i++){
            pref[p[i] + 1] = st[p[i]].size();
        }
        for (i64 i = 0; i < 5; i++){
            pref[i + 1] += pref[i];
        }
        // printmsg("pref=", pref, pref+6);
        vector<bool> skip(n, false);
        i64 cnt = 0;
        for (i64 i = 0; i < n; i++){
            if (skip[i]) continue;
            auto[u, v] = c[i];
            i64 place = pref[p[u]] + pos[u][v];
            if (place != i){
                auto[u2, v2] = c[place];
                if (pref[p[u2]] + pos[u2][v2] == i){
                    skip[place] = true;
                }
                ++cnt;
            }
        }
        ans = min(ans, cnt);
    } while (next_permutation(p, p + 4));
    cout << ans << endl;
}

signed main(){
    fastio;
    solve();
}
