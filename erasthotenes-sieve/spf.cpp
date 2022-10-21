/* 
Given N, calculates the smallest prime factor (spf) that divides K for each 1 <= K <= N
If K is prime, that prime factor will be K itself
*/

#include <bits/stdc++.h>
using namespace std;

void spf(int N, int ans[]){
  // ans is a N+1 sized array
  for (int i = 0; i <= N; i++){
    ans[i] = i;
  }
  
  int is_prime[N+1]; // 0 means is prime, 1 means is composite
  memset(is_prime, is_prime + N + 1, 0);
  is_prime[0] = 1; is_prime[1] = 1;
  for (int i = 2; i <= N; i++){
    if (is_prime[i] == 0){
      for (int mul = i; mul <= N; mul += i){
        ans[mul] = min(ans[mul], i); 
        // last value will be the smallest divisor of mul greater than 1 (which is the spf) 
        
      }
    }
  }

}
