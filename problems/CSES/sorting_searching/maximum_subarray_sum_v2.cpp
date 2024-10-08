/*
Let m[i] = min(1 <= j <= i)sum(1 <= l < j)a[l] = min(1 <= j <= i)ps[j - 1] be the minimum
prefix sum up to index i (but NOT INCLUDING)
so m[0] = 0 (empty sum)

It can be computed on O(n)
using 
    prefix sum + prefix min

then the maximum subarray sum is
max(0 <= i < n)(sum(0 <= j <= i)a[i] - m[i + 1]) = max(0 <= i < n)(ps[i] - m[i])
where ps[i] - m[i] is the MAXIMUM subarray sum that ENDS in a[i] (necessarily contains a[i])

of course we can't use m[n] since either it's the same as m[n - 1] or it is the entire 
array ==> the only possible resulting difference, s[n - 1] - m[n], would be 0
*/

#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

template <typename num> void ps(num a[], i64 n){
    for (i64 i = 1; i < n; i++){
        a[i] += a[i - 1];
    }
}

signed main(){
    i64 n;
    cin >> n;
    i64 a[n], m[n + 1], s[n]; // sum of x<=1e9 over n<=2e5 can overflow i64
    m[0] = 0;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        m[i+1] = a[i];
        s[i] = a[i];
    }
    // prefix sum 
    ps(m, n + 1);
    ps(s, n);
    // prefix min
    for (i64 i = 1; i < n + 1; i++){
        m[i] = min(m[i], m[i-1]);
    }

    i64 total = -1e18; // random array element to initialize it
    for (i64 i = 0; i < n; i++){
        // disregard M[0] - m[0] (empty subarray)
        total = max(total, s[i] - m[i]);
    }
    cout << total << endl;
}
