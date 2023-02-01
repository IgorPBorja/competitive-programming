#include <bits/stdc++.h>
using namespace std;

/*
kadane's algorithm:
-> Let E[k] := max{1 <= i <= k}(sum(A[i..k]))
be the maximum subarray sum over all NON-EMPTY subarrays that end in k
-> Then E[k+1] = max(A[k+1], E[k] + A[k+1])
  since we either pick elements before A[k+1] (the only mandatory for E[k+1]) or we don't
-> In the end we must have ANS = max{1 <= k <= n}(E[k])
*/

int main(){
  int n;
  cin >> n;
  int a[n];
  long long end[n] = {0};
  for (int i = 0; i < n; i++) cin >> a[i];

  long long ans = a[0];               // the chosen subarray can't be empty
  end[0] = a[0];
  for (int i = 1; i < n; i++){
    end[i] = a[i] + max((long long)0, end[i-1]);
    ans = max(ans, end[i]);
  }
  cout << ans;
}