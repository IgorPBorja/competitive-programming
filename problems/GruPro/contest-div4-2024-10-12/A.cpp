#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; 
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int dp[n];
    dp[0] = 1;
    for (int i = 1; i < n; i++){
        dp[i] = (a[i - 1] < a[i]) ? 1 + dp[i - 1] : 1;
    }
    cout << *std::max_element(dp, dp + n) << endl;
}