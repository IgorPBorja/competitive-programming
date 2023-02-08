#include <bits/stdc++.h>
using namespace std;

// at each iteration i
// sums[k] = #(j < i : sum(0 <= l <= j)a[l] = k)

int main(){
    int n, x; 
    cin >> n >> x;
    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    map<long long, long long> sums;
    sums[0] = 1; // empty subarray
    long long s = 0, ans = 0;
    for (int i = 0; i < n; i++){
        s += a[i];
        // s = ps[i] now
        // we need all j < i such that ps[i] - ps[j] = x
        ans += sums[s - x];
        ++sums[s]; // update ans
    }
    cout << ans;
}