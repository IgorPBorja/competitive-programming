#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

int main(){
    i64 l = 0, r = (2147483647ll * (i64)(1000 + 100));
    i64 n;
    cin >> n;
    for (i64 i = 1; i <= n; i++){
        string s;
        cin >> s;
        if (s == "?") continue;
        i64 x = (i64)stoi(s);
        // from k/i ranges from x-0.5 to x+0.5 (open on the right)
        // so x - 1/2 <= k/i < x + 1/2
        // <==> 2x - 1 <= 2 * k/i < 2x + 1
        // <==> 2xi - i <= 2 * k <= 2xi + i - 1
        // <==> xi - i / 2 <= k <= xi + i / 2 - 1
        // <==> xi - floor(i / 2) <= k <= xi + floor(i / 2) - 1
        l = max(l, x * i - i / 2);
        r = min(r, x * i + i / 2 - 1);
    }
    // the problem guarantees unicity ==> l == r
    cout << l << endl;
}