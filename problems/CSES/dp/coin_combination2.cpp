#include<bits/stdc++.h>
using namespace std;

/*
Construct solutions from array: 
* every ordered solution can be represented as a n-uple (k_1, ... k_n)
  where k_i is the amount of times c[i] appears in the sum
* however, code this solution BOTTOM UP
*/


int main(){
  const int MOD = 1e9 + 7;
  int n, x;
  cin >> n >> x;
  int c[n];
  for (int i = 0; i < n; i++){
    cin >> c[i];
  }
  int dp[x + 1] = {0};
  dp[0] = 1;

  for (int i = 0; i < n; i++){
    for (int s = c[i]; s <= x; s++){
      dp[s] = (dp[s] + dp[s - c[i]]) % MOD;
    }
  }
  cout << dp[x];
}