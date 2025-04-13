#include <bits/stdc++.h>
using namespace std;
 
const int MOD = (int)1e9 + 7;  // NOTE: MIGHT CHANGE

int bexp(int a, int p){
    if (p == 0){
        return 1;
    } else {
        int m = bexp(a, p / 2);
        if (p % 2 == 1){
            return (((m * m) % MOD) * a) % MOD;
        } else {
            return (m * m) % MOD;
        }
    }
}

int inv(int a){
    return bexp(a, MOD - 2);
}