#include <bits/stdc++.h>
using namespace std;

// let b[0..n-1] be such that
// b[i] = #{j | sum(0 <= k < j)a[k] = i mod n} = #{j | ps[j - 1] = i mod n}
// then 
// ANSWER = sum(0 <= i <= n)choose(b[i], 2)

int main(){
    int n;
    cin >> n;
    long long a[n], ps[n + 1];
    ps[0] = 0;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        ps[i+1] = a[i];
    }
    for (int i = 1; i < n + 1; i++){
        ps[i] += ps[i-1];
    }

    long long b[n] = {(long long)0};
    for (int i = 0; i < n + 1; i++){
        // we need to make ps[i] positive 
        // since modulo for negative is broken in cpp
        // ==> ps[i] -> ps[i] + n*ceil(abs(ps[i])/n)
        // = ps[i] + n * floor((abs(ps[i]) + n - 1) / n)
        if (ps[i] >= 0){
            ++b[ps[i] % n];
        } else {
            long long v = ps[i] + n * ( (abs(ps[i]) + n - 1)/n );
            ++b[v % n];
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; i++){
        // has to choose 2 different indices j1,j2 such that ps[j1] = ps[j2] = i mod n
        // then (if j2 > j1) ps[j2] - ps[j1] = a[j1] + ... + a[j2 - 1] = 0 mod n 
        ans += (b[i]*(b[i]-1)) / 2;
    }
    cout << ans;
}