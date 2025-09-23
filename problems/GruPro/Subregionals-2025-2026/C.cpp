#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

int main(){
    // polynomial is represented as binary repr of number
    i64 n;
    cin >> n;
    i64 x = 0;
    for (i64 i = n; i >= 0; i--){
        i64 a;
        cin >> a;
        x |= (a * (1ll << i));
    }

    i64 ops = 0;
    while (x != 1){
        ++ops;
        if (x % 2 == 0) {  // no constant term
            x >>= 1;
        } else {
            // mod 2 sum of xP(x), P(x) and 1
            x = x ^ (x << 1) ^ 1;
        }
    }
    cout << ops << endl;
}