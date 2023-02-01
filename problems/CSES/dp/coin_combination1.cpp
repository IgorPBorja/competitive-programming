#include <bits/stdc++.h>
using namespace std;

int main(){
  const long long MOD = 1e9 + 7; 
  int n, x;
  cin >> n >> x;
  long long c[n];
  for (int i = 0; i < n; i++){
    cin >> c[i];
  }
  sort(c, c + n);
  
  long long dp[x + 1] = {0};
  dp[0] = 1;

  for (int i = 0; i < x + 1; i++){
    for (int j = 0; j < n && c[j] <= i; j++){
      dp[i] = (dp[i] + dp[i - c[j]]) % MOD;
    }
  }
  cout << dp[x];
}