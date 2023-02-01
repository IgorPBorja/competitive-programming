// In general: this approach to the sum of k-values problem is O(n^{k-1}log n)
// is there a better one?

#include <bits/stdc++.h>
using namespace std;

int bsearch(long long a[], int n, long long x){
  int lo = 0, hi = n - 1;
  while(lo <= hi){
    int mid = lo + (hi - lo)/2;
    if (a[mid] == x){
      return mid;
    } else if (x < a[mid]){
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  return -1;
}

int main(){
  int n;
  long long x;
  cin >> n >> x;
  long long a[n], sorted[n];
  for (int i = 0; i < n; i++){
    cin >> a[i];
    sorted[i] = a[i];
  }
  sort(sorted, sorted + n);

  for (int i = 0; i < n; i++){
    for (int j = i + 1; j < n; j++){
      int query_res = bsearch(sorted, n, x - a[i] - a[j]);
      if (query_res != -1){
        // O(n)
        for (int k = 0; k < n; k++){
          if (a[k] == x - a[i] - a[j] && k != i && k != j){
            cout << i + 1 << ' ' << j + 1 << ' ' << k + 1 << '\n';
            // the +1 compensates the 1-indexing
            return 0;
          }
        }
      }
    }
  }
  // O(n^2 + n) = O(n^2)
  cout << "IMPOSSIBLE";
}