#include <bits/stdc++.h>
using namespace std;
 
#define i64 int64_t

// factor a single number in O(sqrt(x))
// return list of pairs (p, p^vp(x))
vector<pair<i64, i64>> factor(i64 x){
    vector<pair<i64, i64>> f;
    for (i64 p = 2; p * p <= x; p++){
        if (x % p == 0){
            i64 pk = 1;
            while (x % p == 0){
                pk *= p;
                x /= p;
            }
            f.emplace_back(p, pk);
        }
    }
    if (x > 1) {  // what remains is a prime
        f.emplace_back(x, x);
    }
    return f;
}

i64 period(const vector<pair<i64, i64>> factorization){
    i64 q = 1;
    for (auto[p, pk]: factorization){
        i64 period_pk;
        if (p == 2){
            period_pk = (pk / 2) * 3;
        } else if (p == 5){
            period_pk = (pk / 5) * 20;
        } else {
            period_pk = (pk / p) * (p * p - 1);
        }
        q = (q / __gcd(q, period_pk)) * period_pk;  // safe lcm (should not overflow long long)
    }
    return q;
}

i64 bexp_period(i64 a, i64 p, i64 period){
    // if b = 2^i1 + ... + 2^ik
    // then we keep squaring 
    // and multiply the base number when we get to some active bit
    __int128_t res = 1;
    __int128_t power = a;
    for (i64 i = 0; i < 32; i++, power = (power * power) % (__int128_t)period){
        if (p & (1ll << i)){
            res = (res * power) % (__int128_t)period;          
        }
    }
    return res;
}

vector<vector<i64>> matmul(
    const vector<vector<i64>>& A, const vector<vector<i64>>& B,
    i64 mod
){
    vector<vector<i64>> C(2, vector<i64>(2));
    for (i64 i = 0; i < 2; i++){
        for (i64 j = 0; j < 2; j++){
            C[i][j] = 0;
            for (i64 k = 0; k < 2; k++){
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return C;
}

vector<vector<i64>> mat_bexp(vector<vector<i64>> A, i64 p, i64 mod){
    vector<vector<i64>> Id(2, vector<i64>(2, 0));
    Id[0][0] = Id[1][1] = 1;
    vector<vector<i64>> B = A;
    vector<vector<i64>> C = Id;
    // period might be up to 10^18 <= 2^60
    for (i64 i = 0; i < 63; i++, B = matmul(B, B, mod)){
        if (p & (1ll << i)){
            C = matmul(C, B, mod);
        }
    }
    return C;
}

signed main(){
    i64 a, b, M;
    cin >> a >> b >> M;

    // F^k = ((f[k + 1], f[k]), (f[k], f[k - 1]))
    vector<vector<i64>> F(2, vector<i64>(2, 0));
    F[0][0] = F[0][1] = F[1][0] = 1;
    i64 period_multiple = period(factor(M));
    i64 exp = bexp_period(a, b, period_multiple);
    vector<vector<i64>> Fpow = mat_bexp(F, exp, M);

    cout << Fpow[0][1] << endl;
}
