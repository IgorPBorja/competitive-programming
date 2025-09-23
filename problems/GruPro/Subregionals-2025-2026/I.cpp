#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

int main(){
    i64 n;
    cin >> n;
    vector<i64> x(n), y(n);
    for (i64 i = 0; i < n; i++) cin >> x[i] >> y[i];

    auto d1 = [&x, &y](i64 i, i64 j){
        return abs(x[i] - x[j]) + abs(y[i] - y[j]);
    };

    i64 a = 1, b = d1(0, 1) - 1;
    // i -> i + 1
    if (a > b){
        cout << -1 << endl;
        return 0;
    }
    for (i64 i = 1; i + 1 < n; i++){
        i64 d_prev = d1(i - 1, i), d_next = d1(i, i + 1);
        // [a,b] -> min value is at least 1 and at least d_prev - previous max = d_prev - b
        // [a,b] -> max value is at most d_next-1 and at most d_prev - previous min = d_prev - a
        i64 a2 = max((i64)1, d_prev - b),
            b2 = min(d_next - 1, d_prev - a);
        if (a2 > b2){
            cout << -1 << endl;
            return 0;
        }
        a = a2, b = b2;
    }
    // now backtrack

    // we have e = n - 1 edges
    // if e is even, then max forces min at the end
    // else, max forces max
    i64 r;
    if ((n - 1) % 2 == 0) r = a;
    else r = b;

    // we are at i0 = n-2, and we want to go 
    // to go to i - 1 > 0 with distance d_prev
    // then r = d_prev - r_prev ==> r_prev = d_prev - d
    for (i64 i = n - 2; i - 1 >= 0; i--){
        i64 d_prev = d1(i - 1, i);
        r = d_prev - r;
    }
    cout << r << endl;
}