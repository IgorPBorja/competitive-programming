#include <bits/stdc++.h>

using namespace std;
#define i64 int64_t
#define all(a) a.begin(),a.end();

const i64 MOD = (i64)998244353;

i64 bexp(i64 a, i64 p){
    if (p == 0){
        return 1;
    } else {
        const i64 b = bexp(a, p / 2);
        const i64 b2 = (b * b) % MOD;
        if (p % 2 == 0) return b2;
        else return (a * b2) % MOD;
    }
}

vector<vector<i64>> mul(const vector<vector<i64>>& a, const vector<vector<i64>>& b){
    const i64 n = a.size(), p = a[0].size(), m = b[0].size();
    vector<vector<i64>> c(n, vector<i64>(m));
    for (i64 i = 0; i < m; i++){
        for (i64 j = 0; j < n; j++){
            c[i][j] = 0;
            for (i64 k = 0; k < p; k++){
                // fermat theorem
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % (MOD - 1);
            }
        }
    }
    return c;
}

vector<vector<i64>> vbexp(vector<vector<i64>> a, i64 p){
    if (p == 0){
        vector<vector<i64>> res(2, vector<i64>(2));
        for (i64 i = 0; i < 2; i++){
            res[i][i] = 1;
        }
        return res;
    } else {
        const auto b = vbexp(a, p / 2);
        const auto b2 = mul(b, b);
        if (p % 2 == 0) return b2;
        else return mul(a, b2);
    }
}




void solve(){
    // exponent is fibonnacci sequence
    // 0 1
    // 1 1
    vector<vector<i64>> base = {{0, 1}, {1, 1}};
    i64 n;
    cin >> n;
    if (n == 0){
        cout << 1 << endl;
        return;
    }
    vector<vector<i64>> m = vbexp(base, n - 1);
    
    // m * [0, 1] ==> (m[0][1], m[1][1])
    i64 e = m[1][1] % (MOD - 1);
    cout << bexp(2ll, e) << endl;
}

signed main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(t--)solve();
}
