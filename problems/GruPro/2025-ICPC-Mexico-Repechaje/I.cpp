#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define print(msg, v) cerr << msg; for (auto x: v) cerr << x << " "; cerr << endl

#define i64 int64_t

// max(2m + 1 : (2m + 1)^2 <= x)
i64 odd_lvl(i64 x){
    // avoid r*r overflowing
    i64 l = 0, r = (i64)1e6, ans = 0;
    while (l <= r){
        const i64 m = l + (r - l) / 2;
        if ((2 * m + 1) * (2 * m + 1) <= x){
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return 2 * ans + 1;
}

pair<i64, i64> dir[4] = {
    pair<i64, i64>(-1, 0), // left
    pair<i64, i64>(0, -1),  // up
    pair<i64, i64>(1, 0),  // right
    pair<i64, i64>(0, 1), // down
};

// worst diff is sqrt(M)^2 - (sqrt(M) - 1)^2 = O(sqrt(M))
// so can't simulate all
signed main(){
    fastio;
    i64 n, x;
    cin >> n;
    for (i64 i = 0; i < n; i++){
        cin >> x;
        i64 k = odd_lvl(x), d = x - k * k;  // in-level offset
        // we can suppose WLOG new spiral level always starts down at the right
        // since lvl is odd

        i64 dx = (k / 2), dy = ((k + 1) / 2), idx = 0;

        // left, up, right, then down
        // goes from dx to -dx-1 on left movement
        // then dy to -dy on up movement
        // then -dx-1 to dx+1 on right movement
        // then -dy to dy on down movement
        vector<i64> sizes = {
            dx - (-dx - 1),
            (dy - (-dy)),
            (dx + 1 - (-dx - 1)),
            (dy - (-dy))
        };

        while (d > 0){
            if (d >= sizes[idx]){
                dx += sizes[idx] * dir[idx].first;
                dy += sizes[idx] * dir[idx].second;
                d -= sizes[idx];
                ++idx;
            } else {
                dx += d * dir[idx].first;
                dy += d * dir[idx].second;
                break;
            }
        }
        cout << 4ll * abs(dx) * abs(dx) + 4ll * abs(dy) * abs(dy) << endl;
    }
}