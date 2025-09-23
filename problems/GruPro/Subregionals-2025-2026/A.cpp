#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> a(n, vector<i64>(m));
    vector<i64> val_max(m, 0);
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            cin >> a[i][j];
            val_max[j] = max(val_max[j], a[i][j]);
        }
    }
    i64 s = 0;
    for (i64 x: val_max) s += x;
    cout << s << endl;
}