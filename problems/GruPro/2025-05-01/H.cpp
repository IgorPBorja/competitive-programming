#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

i64 argmin(const vector<i64>& v){
    i64 p = 0;
    for (i64 i = 1; i < v.size(); i++){
        if (v[i] < v[p]){
            p = i;
        }
    }
    return p;
}

int main(){
    i64 n, a, k, p;
    cin >> n >> a >> k >> p;
    vector<i64> largest;
    largest.emplace_back(a);

    for (i64 i = 2; i <= n; i++){
        a = (a * k) % p;
        if (largest.size() < 5){
            largest.emplace_back(a);
        } else {
            i64 sub = argmin(largest);
            if (a > largest[sub]){
                largest[sub] = a;
            }
        }
    }
    sort(largest.begin(), largest.end());
    for (i64 x: largest){
        cout << x << " ";
    }
    cout << endl;
}