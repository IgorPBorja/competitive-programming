#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define printmsg(msg, first, last) cout << msg;for(auto it=first;it!=last;it++)cout<<*it<<" ";cout<<endl
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

const i64 MOD = (i64)1e9 + 7;

const i64 D = 0;
const i64 U = 1;
const i64 L = 2;
const i64 R = 3;

i64 dx[4] = {1, -1, 0, 0};
i64 dy[4] = {0, 0, -1, 1};

int main(){
    fastio;

    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> a(n, vector<i64>(m));
    pair<i64, i64> dp[4][n][m];

    for (i64 i = 0; i < n; i++){
        string row;
        cin >> row;
        for (i64 j = 0; j < m; j++){
            if (row[j] == '.'){
                a[i][j] = 1;
            } else {
                a[i][j] = 0;
            }
        }
    }

    auto can_walk = [&a, n, m](i64 i, i64 j, i64 dx, i64 dy){
        if (i + dx < 0 || i + dx >= n) return false;
        if (j + dy < 0 || j + dy >= m) return false;
        return (bool)(a[i + dx][j + dy]);
    };

    // down dp
    for (i64 i = n - 1; i >= 0; i--){
        for (i64 j = 0; j < m; j++){
            if (can_walk(i, j, dx[D], dy[D])){
                dp[D][i][j] = dp[D][i + dx[D]][j + dy[D]];
            } else {
                dp[D][i][j] = make_pair(i, j);
            }
        }
    }
    // up dp
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            if (can_walk(i, j, dx[U], dy[U])){
                dp[U][i][j] = dp[U][i + dx[U]][j + dy[U]];
            } else {
                dp[U][i][j] = make_pair(i, j);
            }
        }
    }
    // left dp
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            if (can_walk(i, j, dx[L], dy[L])){
                dp[L][i][j] = dp[L][i + dx[L]][j + dy[L]];
            } else {
                dp[L][i][j] = make_pair(i, j);
            }
        }
    }
    // right dp
    for (i64 i = 0; i < n; i++){
        for (i64 j = m - 1; j >= 0; j--){
            if (can_walk(i, j, dx[R], dy[R])){
                dp[R][i][j] = dp[R][i + dx[R]][j + dy[R]];
            } else {
                dp[R][i][j] = make_pair(i, j);
            }
        }
    }

    string s;
    cin >> s;
    pair<i64, i64> pos = make_pair(n - 1, 0);  // bottom left
    for (char c: s){
        if (c == 'D'){
            pos = dp[D][pos.first][pos.second];
        } else if (c == 'U'){
            pos = dp[U][pos.first][pos.second];
        } else if (c == 'L'){
            pos = dp[L][pos.first][pos.second];
        } else if (c == 'R'){
            pos = dp[R][pos.first][pos.second];
        }
        // cout << "after c=" << c << " went to pos=(" << pos.first << "," << pos.second << ")" << endl;
    }

    // axis is inverted in the up/down section, and left/right is first
    cout << pos.second + 1 << " " << (n - 1 - pos.first) + 1 << endl;
}