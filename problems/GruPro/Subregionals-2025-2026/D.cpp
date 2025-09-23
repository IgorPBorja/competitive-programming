#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

/*
SOS DP: A[mask] = 1 if mask is winnable, else 0

We want dp[mask] = sum(submask C mask)A[submask].

So let dp[i][mask] = sum(submask C mask, submask differs - at most - only on bits 0..i-1)A[submask]
= dp[i][mask] = sum(submask C mask, submask XOR mask < 2^i)A[submask]

Then dp[0][mask] = A[mask], and

dp[i][mask] = dp[i - 1][mask] if (i - 1)-th bit is not active.
Else, if mask = 2^i | mask2, then either 
* they differ only in the first i-1 bits
* they differ on the i-th bit too, which means they differ in the first i-1 bits (0..i-2) of mask XOR (2^(i-1)), which is mask2
dp[i][mask] = dp[i - 1][mask] + dp[i-1][mask XOR 2^(i - 1)]

Complexity is O(N 2^N). There are (K * K - K) / 2 + K = K*(K+1)/2 = 6 * 7/2 = 21
possible ordered pairs, and 21 * 2^21 ~ 42 * 10^6 ~ 4.2e7, which passes.
We compute globally for all masks 
*/

constexpr i64 N = 21;

const pair<i64, i64> dominos[N] = {
    {1, 1},
    {1, 2},
    {1, 3},
    {1, 4},
    {1, 5},
    {1, 6},
    {2, 2},
    {2, 3},
    {2, 4},
    {2, 5},
    {2, 6},
    {3, 3},
    {3, 4},
    {3, 5},
    {3, 6},
    {4, 4},
    {4, 5},
    {4, 6},
    {5, 5},
    {5, 6},
    {6, 6}
};

i64 get_pos(pair<i64, i64> a) {
    for (i64 i = 0; i < N; i++) {
        if (dominos[i] == a) return i;
    }
    assert(0 == 1);
    return -1;  // should never happen
}

struct dsu {
    i64 p[6] = {0, 1, 2, 3, 4, 5};
    i64 sz[6] = {1, 1, 1, 1, 1, 1};

    i64 find(i64 x){
        return (p[x] == x ? x : p[x] = find(p[x]));
    }

    void merge(i64 x, i64 y){
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] > sz[y]) swap(x, y);
        p[x] = y;
        sz[y] += sz[x];
    }
};

i64 eval_mask(i64 msk){
    // we codify lexicographic order
    // we can ignore pairs with a=b
    // since a seq is possible/impossible, then adding a pair (x, x) changes nothing

    // build graph of pieces
    vector<i64> deg(6);
    i64 any = -1;
    dsu d;
    for (i64 i = 0; i < N; i++){
        if (msk & (1ll << i)){
            i64 a = dominos[i].first - 1,
                b = dominos[i].second - 1;
            ++deg[a];
            ++deg[b];
            if (any == -1) any = a;
            d.merge(a, b);
        }
    }

    bool ok = true;
    i64 odd = 0;
    any = d.find(any);
    for (i64 i = 0; i < 6; i++) {
        odd += (deg[i] % 2);
        ok &= (deg[i] == 0 || d.find(i) == any);
    }

    return (ok && (odd == 0 || odd == 2));
}

int main(){
    vector<i64> A(1ll << N, 0);
    for (i64 msk = 1; msk < (1ll << N); msk++){
        A[msk] = eval_mask(msk);
    }

    vector<vector<i64>> dp(N + 1, vector<i64>((1ll << N), 0));
    for (i64 msk = 0; msk < (1ll << N); msk++){
        dp[0][msk] = A[msk];
    }

    for (i64 i = 1; i <= N; i++){
        for (i64 msk = 0; msk < (1ll << N); msk++){
            // dp[i]: equal from 2^{N-1} to 2^i
            if (msk & (1ll << (i - 1))){
                dp[i][msk] = dp[i - 1][msk] + dp[i - 1][msk ^ (1ll << (i - 1))];
            } else {
                dp[i][msk] = dp[i - 1][msk];
            }
        }
    }

    i64 t = 0;
    cin >> t;
    for (i64 _ = 0; _ < t; _++){
        i64 n;
        cin >> n;
        i64 mask = 0;
        for (i64 i = 0; i < n; i++){
            i64 a, b;
            cin >> a >> b;
            mask |= (1ll << (get_pos(make_pair(a, b))));
        }
        cout << dp[N][mask] << endl;
    }
}