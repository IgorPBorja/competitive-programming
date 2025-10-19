#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t

vector<i64> sosdp(const vector<i64> A, const i64 B, bool inverse = false){
    assert(A.size() == (1ll << B));
    vector<i64> S = A;
    for (i64 i = 0; i < B; i++){
        // introduce possible diff at i
        for (i64 mask = (1ll << B) - 1; mask >= 0; mask--){
            if (mask & (1ll << i)){
                if (inverse){
                    S[mask] -= S[mask ^ (1ll << i)];
                } else {
                    S[mask] += S[mask ^ (1ll << i)];
                }
            }
        }
    }
    return S;
}
 
vector<i64> not_arr(const vector<i64> A, const i64 B){
    vector<i64> S(1ll << B);
    for (i64 mask = 0; mask < (1ll << B); mask++){
        S[mask] = A[((1ll << B) - 1) ^ mask];
    }
    return S;
}
 
// SOSP(A)[x] = sum(y supermask of x)A[x] = sum(y submask of ~x)A[~y]
// = SOS(~A)[~x] = ~SOS(~A)
// otherwise if SOSP(S) = A then
// ~SOS(~S) = A ==> SOS(~S) = ~A ==> ~S = SOS^{-1}(~A) ==> S = ~SOS^{-1}(~A)
vector<i64> supersetdp(const vector<i64> A, const i64 B, bool inverse = false){
    return not_arr(sosdp(not_arr(A, B), B, inverse), B);
}
