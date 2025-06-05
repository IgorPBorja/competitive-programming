#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define printmsg(msg, first, last) cout << msg; for (auto it = first; it != last; it++) cout << *it << " "; cout << endl

inline bool is_border(const vector<vector<i64>>& a, i64 i, i64 j, i64 n, i64 m){
    bool border = false;
    for (i64 dx = -1; dx <= 1; dx++){
        for (i64 dy = -1; dy <= 1; dy++){
            const i64 i2 = i + dx, j2 = j + dy;
            if (i2 < 0 || i2 >= n) continue;
            if (j2 < 0 || j2 >= m) continue;
            border |= (a[i2][j2] == 0);  // sees white
        }
    }
    return border;
}

vector<vector<i64>> undilate(const vector<vector<i64>>& a){
    const i64 n = a.size();
    const i64 m = a[0].size();
    vector<vector<i64>> b(n, vector<i64>(m));
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            if (a[i][j] == 0 || is_border(a, i, j, n, m)){
                b[i][j] = 0;
            } else {
                b[i][j] = 1;
            }
        }
    }
    return b;
}

vector<vector<i64>> dilate(const vector<vector<i64>>& a){
    const i64 n = a.size();
    const i64 m = a[0].size();
    vector<vector<i64>> b(n, vector<i64>(m, 0));
    // starts with all zeroes
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            if (a[i][j] == 0) continue;  // can't propagate
            for (i64 dx = -1; dx <= 1; dx++){
                for (i64 dy = -1; dy <= 1; dy++){
                    const i64 i2 = i + dx, j2 = j + dy;
                    if (i2 < 0 || i2 >= n) continue;
                    if (j2 < 0 || j2 >= m) continue;
                    b[i2][j2] = 1;
                }
            }
        }
    }
    return b;
}

bool cmp(const vector<vector<i64>>& a, const vector<vector<i64>>& b){
    const i64 n = a.size();
    const i64 m = a[0].size();
    bool eq = true;
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            eq &= (a[i][j] == b[i][j]);
        }
    }
    return eq;
}

signed main(){
    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> a(n, vector<i64>(m));
    for (i64 i = 0; i < n; i++){
        string row;
        cin >> row;
        for (i64 j = 0; j < m; j++){
            a[i][j] = (row[j] == '#');  // 1 if painted
        }
    }
    vector<vector<i64>> b = undilate(a);
    vector<vector<i64>> c = dilate(b);
    if (cmp(a, c)){
        cout << "Possible" << endl;
        for (i64 i = 0; i < n; i++){
            for (i64 j = 0; j < m; j++){
                cout << ((b[i][j] == 1) ? '#' : '.');
            }
            cout << endl;
        }
    } else {
        cout << "Impossible" << endl;
    }
}