#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define i64 int64_t

/*
p[i][j] = max value ending at i and using some subset of books 1..j
f[i][j] = max fame ending at i and using some subset of books 1..j
*/

const i64 TMAX = 780;
const i64 TCLOSE = 480;
const i64 dt = 3;
const i64 INF = 1e15;

signed main(){
    i64 n;
    cin >> n;
    vector<i64> t(n);  // 1-indexed
    vector<i64> vp(n), vf(n);
    for (i64 i = 0; i < n; i++){
        cin >> t[i];
        t[i] *= dt;
    }
    for (i64 i = 0; i < n; i++) cin >> vp[i];
    for (i64 i = 0; i < n; i++) cin >> vf[i];

    i64 p[TMAX + 1][n], f[TMAX + 1][n];
    for (i64 j = 0; j < n; j++){
        p[0][j] = f[0][j] = 0;
    }
    // ending exactly at tf
    for (i64 tf = 1; tf <= TMAX; tf++){
        p[tf][0] = (t[0] <= tf) ? vp[0] : 0;
        f[tf][0] = (t[0] <= tf) ? vf[0] : 0;
        for (i64 i = 1; i < n; i++){
            if (t[i] <= tf && tf - t[i] <= TCLOSE) {
                // can be borrowed at tf-t[i] (before TCLOSE) and read ending at tf
                p[tf][i] = max(p[tf - t[i]][i - 1] + vp[i], p[tf][i - 1]);
                f[tf][i] = max(f[tf - t[i]][i - 1] + vf[i], f[tf][i - 1]);
            } else {
                p[tf][i] = p[tf][i - 1];
                f[tf][i] = f[tf][i - 1];
            }
        }
    }
    i64 p_total = 0, f_total = 0;
    for (i64 tf = 1; tf <= TMAX; tf++) {
        p_total = max(p_total, p[tf][n - 1]);
        f_total = max(f_total, f[tf][n - 1]);
    }
    // cerr << "p_total=" << p_total << " f_total=" << f_total << endl;
    if (p_total > f_total){
        cout << "PLEASURE" << endl;
    } else if (f_total > p_total){
        cout << "FAME" << endl;
    } else cout << "EITHER" << endl;
}